#!/usr/bin/env python

import torch
from matplotlib import pyplot as plt
from pathlib import Path


def make_plot(ax, filename, *args, **kwargs):
    file = Path(filename)
    if not file.exists():
        return

    # Read results
    res = torch.jit.load(file)
    input = dict(res.input.named_buffers())
    output = dict(res.output.named_buffers())
    E = input["forces/E"]
    S = output["state/S"]
    ntime, nbatch, _ = E.shape

    # Plot the curves
    for i in range(nbatch):
        ax.plot(E[:, i, 0], S[:, i, 0], *args, label="batch {}".format(i), **kwargs)


if __name__ == "__main__":
    fig, ax = plt.subplots()

    make_plot(ax, "custom_isotropic_hardening.pt")

    ax.set_xlabel("strain")
    ax.set_ylabel("stress")
    fig.tight_layout()
    fig.savefig("stress_strain_curves.svg")
