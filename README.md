# TinyRO — Ring Oscillator PUF for Intel MAX 10 (with Nios II)

This project implements a small Ring Oscillator (RO) Physical Unclonable Function (PUF) on an Intel MAX 10 FPGA and integrates it with a Nios II soft processor. The hardware is written in VHDL and compiled with Quartus Prime Lite 22.1std. The Nios II application uses the small C library (alt_stdio) to drive a simple request/challenge/enable handshake and collect PUF responses.

The design preserves the RO feedback loops through Quartus using attributes and project settings, and provides a robust top-level FSM to coordinate sampling between the Nios II and the PUF array.

## Device, Tools, and Versions

- FPGA: MAX 10 `10M04SCE144C8G`
- Toolchain: Quartus Prime 22.1std (Lite Edition recommended)
- Nios II SBT for Eclipse or command-line tools (same version)
- Simulation: optional; note that ring oscillators do not oscillate meaningfully in pure functional HDL simulation

## Project Structure

- `TinyRO.qpf`, `TinyRO.qsf`: Quartus project and settings
- VHDL sources (PUF and top):
  - `ring_osc.vhd` — Odd-length ring oscillator with gated loop and preservation attributes
  - `inverter.vhd` / `sky130_fd_sc_hd__inv_2.vhd` — Simple preserved inverter (`notGate`) used by the RO
  - `mux16.vhd` — Generic-width MUX (parameterized by number of inputs and select width)
  - `counter.vhd` — Simple event counter used by the arbiter race
  - `arbiter.vhd` — Chooses the first of two counters to reach threshold
  - `pufbit.vhd` — Builds a single PUF slice: 32 ROs, two MUXes, two counters, and one arbiter
  - `TinyRO.vhd` — Simple PUF-only top (8 parallel bits) for standalone builds
  - `TIny_RO_top.vhd` — Nios-integrated top with a robust FSM (default top for this project)
- Nios II subsystem (Qsys/Platform Designer):
  - `MAX10NIOS/` — Auto-generated system files
  - `MAX10NIOS.qsys`, `MAX10NIOS.sopcinfo` — System definition and metadata
- Software (Nios II small C):
  - `software/puf_small/main.c` — Example app to drive the FSM and collect 128 bits (16×8) with voting
- Constraints, scripts:
  - `SDC1.sdc` — Base timing constraints (add board-specific clock constraints as needed)
  - `config.tcl` — Helper or project config script (optional)

## Hardware Overview

### Ring Oscillator and Preservation

- The RO is an odd-length chain of inverters with a gated feedback (`en`).
- The VHDL uses Quartus-recognized attributes on the feedback nets to prevent optimization:
  - `attribute keep : boolean; attribute noprune : boolean;`
  - Applied to `inter_wire` signals and the RO output tap in `ring_osc.vhd`.
- Project setting required: allow combinational loops in the Quartus project to keep the RO feedback.
  - QSF: `set_global_assignment -name ALLOW_COMBINATIONAL_LOOPS ON`
  - If you don’t see it in the project (TinyRO.qsf), add it and recompile.

### PUF Slice (puf_bit)

- Contains 32 ring oscillators, split into two halves of 16.
- Two generic MUXes select one RO from each half, controlled by an 8‑bit challenge.
  - `mux16.vhd` is generic and adapts automatically when `n_ro` changes. `pufbit.vhd` calculates the select width (`SELW = ceil(log2(n_ro/2))`).
- Two counters integrate the selected RO outputs and an arbiter produces one response bit (`resp`) plus a `finish` flag.

### Top with Nios II (TIny_RO_top)

- Instantiates `N_BITS` PUF slices in parallel (default 8 bits of response).
- Integrates a Nios II system with five memory-mapped PIOs (conduits):
  - `challenge_export[7:0]` (Nios → PUF): challenge value
  - `enabler_export` (Nios → PUF): enable gate for RO
  - `request_export` (Nios → FSM): start a measurement transaction
  - `busy_export` (PUF → Nios): indicates transaction in progress
  - `response_export[7:0]` (PUF → Nios): final response (one bit per PUF slice)

#### FSM Protocol

- `IDLE`: `busy=0`, PUF held in reset, waiting for `request=1`.
- `RECVCHL`: Latch `challenge_export`, wait for `enabler=1`.
- `SETCHL`: Delay a few cycles (`SETTLE_CYCLES` generic, default 8) to settle routing.
- `GETRES`: Release PUF reset and assert enable; wait until all `finish` bits are high.
- `SEND`: Drive `response_export <= resp_vec`. Wait for `request=0`, then return to `IDLE`.
- `WAITREQLOW`: Optional robustness state so software must explicitly drop `request`.

## Building the Hardware

1. Open `TinyRO.qpf` in Quartus Prime.
2. Verify device: `10M04SCE144C8G` (change if your board differs).
3. Verify top-level entity: `TIny_RO_top`.
4. Apply critical settings:
   - Project → Assignments → Settings → Analysis & Synthesis Settings:
     - Ensure combinational loops are allowed: add to QSF if missing:
       `set_global_assignment -name ALLOW_COMBINATIONAL_LOOPS ON`
   - Optional (stability): consider disabling register retiming, duplication, and merging for PUF-adjacent logic if you observe inconsistencies.
5. Pin assignments (example in `TinyRO.qsf`):
   - `clk` → `PIN_27`
   - `rst_n` → `PIN_38`
   - Adjust to your board’s clock/reset pins as needed.
6. Compile the project.
7. Inspect Post‑Fit Netlist Viewer:
   - Drill into `ring_osc` instances; you should see a loop of inverters and an AND gating cell.
   - “Found combinational loop” info messages are expected when loops are allowed.

## Building and Running the Software (Nios II)

The provided application uses the small C library (`alt_stdio`) to run a challenge sweep and collect 128 bits.

- Source: `software/puf_small/main.c`
- Expected PIO base macros (from your BSP `system.h`):
  - `STREAM_0_BASE` (mapped to CHALLENGE PIO)
  - `ENA_BASE`, `REQUEST_BASE` (1‑bit outputs)
  - `BUSY_BASE` (1‑bit input)
  - `RESPONSE_BASE` (8‑bit input)

If your Platform Designer instance names differ, update the macros in `main.c` or define them via compiler flags.

### Build (CLI)

Example flow (adapt paths to your setup):

- Generate BSP (small libc):
  - `nios2-bsp hal_bsp MAX10NIOS.sopcinfo --cpu-name nios2_gen2_0 --set hal.make.bsp_cflags "-Os" --set hal.linker.enable_small_c_library true`
- Create app project with the provided source:
  - `nios2-app --bsp-dir hal_bsp --src-files software/puf_small/main.c --name puf_small`
- Build and download:
  - `nios2-app --build --app-dir puf_small`
  - `nios2-download -g output_files/TinyRO.sof`
  - `nios2-download puf_small.elf -g`
  - `nios2-terminal`

Alternatively, use Nios II SBT for Eclipse to create a small C app and add `main.c`.

### App Behavior

- Configuration (in `main.c`):
  - `N_ROUNDS = 16` (16 bytes → 128 bits total)
  - `SAMPLES_PER_CHALL = 1000`
  - Challenge sequence: start at `CHALLENGE_SEED` (default 0x3C), then increment by `CHALLENGE_STEP` (default 0x01) each round
- Measurement for each challenge:
  1. Write `challenge_export`.
  2. Set `request_export=1` and `enabler_export=1`.
  3. Wait for `busy_export=1` and a short guard delay.
  4. Read `response_export[7:0]`.
  5. Set `request_export=0` and `enabler_export=0`, then wait for `busy_export=0`.
  6. Repeat steps 1–5 `SAMPLES_PER_CHALL` times and majority‑vote each bit.
- Output:
  - Prints per‑round challenge, voted response, and rough per‑bit ones fraction.
  - Prints final 16‑byte (128‑bit) PUF response and a 4×32‑bit view.

## Notes and Troubleshooting

- RO not present after fitting: ensure `ALLOW_COMBINATIONAL_LOOPS ON` is set and that `ring_osc.vhd` nets have `keep`/`noprune` attributes. Post‑Fit netlist should show a LUT chain in a feedback loop with a gating AND.
- VHDL aggregate error with `others => '1'`: use `(finish_vec'range => '1')` to match vector bounds (fixed in `TIny_RO_top.vhd`).
- MUX width errors after changing `n_ro`: use the generic `mux16.vhd` and let `pufbit.vhd` compute `SELW = ceil(log2(n_ro/2))` (already implemented).
- Avoid simulation expectations: pure HDL simulation will not emulate analog RO behavior. Validate on hardware.
- Stability: for consistent PUF behavior, avoid aggressive optimizations near RO/counters. If needed, disable register retiming/duplication/merging and preserve hierarchy at the PUF region.

## Customization

- Change response width: set `N_BITS` generic in `TIny_RO_top.vhd` and widen `response_export` PIO in Platform Designer accordingly.
- Adjust RO stage count: edit `num_inv` in `ring_osc.vhd` (keep it odd). If you change `n_ro` in `pufbit.vhd`, the MUX select width adapts automatically.
- FSM settle time: tweak `SETTLE_CYCLES` generic in `TIny_RO_top.vhd`.
- Collection via shift register: `shiftreg16.vhd` is provided if you want to collect one response bit across multiple triggers.

## Credits and License

- Portions of the original Tiny Tapeout demo top-level are adapted (see `TinyRO.vhd`).
- Unless otherwise specified in individual files, consider this project under the license header(s) present in the source files. If a formal LICENSE file is required, please add it to the repository root.

