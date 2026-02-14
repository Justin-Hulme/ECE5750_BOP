import subprocess
import re
import csv

bins = ["perceptron-no-no-BOP-no-ship-1core"]

traces = [
    "600.perlbench_s-210B.champsimtrace.xz",
    "627.cam4_s-573B.champsimtrace.xz",
    "602.gcc_s-734B.champsimtrace.xz",
    "628.pop2_s-17B.champsimtrace.xz",
    "603.bwaves_s-3699B.champsimtrace.xz",
    "631.deepsjeng_s-928B.champsimtrace.xz",
    "605.mcf_s-665B.champsimtrace.xz",
    "638.imagick_s-10316B.champsimtrace.xz",
    "607.cactuBSSN_s-2421B.champsimtrace.xz",
    "641.leela_s-800B.champsimtrace.xz",
    "619.lbm_s-4268B.champsimtrace.xz",
    "644.nab_s-5853B.champsimtrace.xz",
    "620.omnetpp_s-874B.champsimtrace.xz",
    "648.exchange2_s-1699B.champsimtrace.xz",
    "621.wrf_s-575B.champsimtrace.xz",
    "649.fotonik3d_s-1176B.champsimtrace.xz",
    "623.xalancbmk_s-700B.champsimtrace.xz",
    "654.roms_s-842B.champsimtrace.xz",
    "625.x264_s-18B.champsimtrace.xz",
    "657.xz_s-3167B.champsimtrace.xz",
]

rows = []

for trace in traces:
    for bin in bins:
        print(f"running {trace} with bin {bin}")
        result_file = f"results_50M/{trace}-{bin}.txt"

        subprocess.run(["./run_champsim.sh", bin, "1", "10", trace], check=True)

        data = {
            "trace": trace,
            "bin": bin,
            "ipc": None,

            "l2c_total_access": 0, "l2c_total_hit": 0, "l2c_total_miss": 0,
            "l2c_load_access": 0, "l2c_load_hit": 0, "l2c_load_miss": 0,
            "l2c_rfo_access": 0, "l2c_rfo_hit": 0, "l2c_rfo_miss": 0,
            "l2c_prefetch_access": 0, "l2c_prefetch_hit": 0, "l2c_prefetch_miss": 0,
            "l2c_writeback_access": 0, "l2c_writeback_hit": 0, "l2c_writeback_miss": 0,

            "l2c_pref_requested": 0, "l2c_pref_issued": 0,
            "l2c_pref_useful": 0, "l2c_pref_useless": 0,

            "l2c_avg_miss_latency": 0.0,
        }

        with open(result_file, "r") as file:
            for line in file:

                # IPC
                ipc_match = re.search(r"cumulative IPC:\s*(\d+\.\d+)", line)
                if ipc_match:
                    data["ipc"] = float(ipc_match.group(1))

                # L2C TOTAL / LOAD / RFO / PREFETCH / WRITEBACK
                match = re.match(
                    r"L2C (TOTAL|LOAD|RFO|PREFETCH|WRITEBACK)\s+ACCESS:\s+(\d+)\s+HIT:\s+(\d+)\s+MISS:\s+(\d+)",
                    line,
                )
                if match:
                    kind = match.group(1).lower()
                    data[f"l2c_{kind}_access"] = int(match.group(2))
                    data[f"l2c_{kind}_hit"] = int(match.group(3))
                    data[f"l2c_{kind}_miss"] = int(match.group(4))

                # PREFETCH REQUESTED / ISSUED / USEFUL / USELESS
                match = re.match(
                    r"L2C PREFETCH\s+REQUESTED:\s+(\d+)\s+ISSUED:\s+(\d+)\s+USEFUL:\s+(\d+)\s+USELESS:\s+(\d+)",
                    line,
                )
                if match:
                    data["l2c_pref_requested"] = int(match.group(1))
                    data["l2c_pref_issued"] = int(match.group(2))
                    data["l2c_pref_useful"] = int(match.group(3))
                    data["l2c_pref_useless"] = int(match.group(4))

                # AVERAGE MISS LATENCY
                match = re.match(
                    r"L2C AVERAGE MISS LATENCY:\s+([\d\.]+)",
                    line,
                )
                if match:
                    data["l2c_avg_miss_latency"] = float(match.group(1))

        rows.append(data)

# Write CSV
with open("results.csv", "w", newline="") as f:
    writer = csv.DictWriter(f, fieldnames=rows[0].keys())
    writer.writeheader()
    writer.writerows(rows)