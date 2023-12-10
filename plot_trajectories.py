import torch
from matplotlib import pyplot as plt
from pathlib import Path


def make_plot(ax, filename, *args, **kwargs):
    file = Path(filename)
    if not file.exists():
        return

    # Read results
    res = torch.jit.load(file)
    output = dict(res.output.named_buffers())
    x = output["state/x"]
    ntime, nbatch, dim = x.shape

    # Plot the trajectories
    for i in range(nbatch):
        ax.plot(x[:, i, 0], x[:, i, 1], *args, label="batch {}".format(i), **kwargs)


if __name__ == "__main__":
    fig, ax = plt.subplots()

    make_plot(ax, "flying_ball_in_air.pt", "k-")
    make_plot(ax, "flying_ball_in_glue.pt", "r--")

    ax.set_xlabel("x")
    ax.set_ylabel("y")
    fig.tight_layout()
    fig.savefig("trajectories.svg")
