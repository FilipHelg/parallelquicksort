import numpy as np
import matplotlib.pyplot as plt


def main():
	data = np.genfromtxt("results.csv", delimiter=",", names=True, dtype=None, encoding="utf-8")

	distributions = ["u", "n", "e"]
	names = {"u": "Uniform", "n": "Normal", "e": "Exponential"}

	fig, axes = plt.subplots(1, 3, figsize=(12, 4), sharey=True)

	for ax, d in zip(axes, distributions):
		sub = data[data["d"] == d]
		n_max = int(np.max(sub["n"]))
		sub = sub[sub["n"] == n_max]

		threads = np.array(sorted(np.unique(sub["t"])), dtype=int)
		times = np.array([sub[sub["t"] == t]["result"][0] for t in threads], dtype=float)

		t1 = times[threads == 1][0]
		speedup = t1 / times

		ax.plot(threads, speedup, marker="o")
		ax.set_title(names[d])
		ax.set_xlabel("Threads")
		ax.set_xticks([1, 2, 4, 8, 16])
		ax.grid(True, alpha=0.3)

	axes[0].set_ylabel("Relative speedup")
	fig.suptitle("Relative speedup vs number of threads (largest n)")
	fig.tight_layout()
	fig.savefig("speedup.png", dpi=200)
	print("Saved figure to speedup.png")

	# Separate figure: all measured runtimes and a fitted n*log2(n) curve.
	n_vals = data["n"].astype(float)
	time_vals = data["result"].astype(float)

	theory_base = n_vals * np.log2(n_vals)
	scale = np.dot(theory_base, time_vals) / np.dot(theory_base, theory_base)

	order = np.argsort(n_vals)
	n_sorted = n_vals[order]
	theory_sorted = scale * n_sorted * np.log2(n_sorted)

	fig2, ax2 = plt.subplots(figsize=(7, 5))
	ax2.scatter(n_vals, time_vals, s=35, alpha=0.8, label="Measured data")
	ax2.plot(n_sorted, theory_sorted, color="red", linewidth=2, label="Fitted c*n*log2(n)")
	ax2.set_xscale("log")
	ax2.set_yscale("log")
	ax2.set_xlabel("n")
	ax2.set_ylabel("Runtime (s)")
	ax2.set_title("All data points vs theoretical n log2(n)")
	ax2.grid(True, which="both", alpha=0.3)
	ax2.legend()
	fig2.tight_layout()
	fig2.savefig("nlogn_all_points.png", dpi=200)
	print("Saved figure to nlogn_all_points.png")


if __name__ == "__main__":
	main()
