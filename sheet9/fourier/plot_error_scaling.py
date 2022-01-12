#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
rc('text', usetex=True)

k = 7 # vary from 0-9

e_s_b = np.loadtxt("error_scaling_simpson_b.dat")
e_t_b = np.loadtxt("error_scaling_trapezoid_b.dat")

e_s_a = np.loadtxt("error_scaling_simpson_a.dat")
e_t_a = np.loadtxt("error_scaling_trapezoid_a.dat")

n = np.arange(10,10000,100)

fig, ax = plt.subplots(1, 2, figsize=(8,4))

# Plot a components
ax[0].plot(n,e_t_a[k,:],label="trapezoid a")
ax[0].plot(n,e_s_a[k,:],label="simpson a")

# Plot b components
ax[1].plot(n,e_t_b[k,:],label="trapezoid b")
ax[1].plot(n,e_s_b[k,:],label="simpson b")

ax[0].legend(fontsize=14)
ax[1].legend(fontsize=14)

ax[0].set_yscale("log")
ax[0].set_xscale("log")
ax[1].set_yscale("log")
ax[1].set_xscale("log")

ax[0].set_xlabel('$n$', fontsize=18)
ax[1].set_xlabel('$n$', fontsize=18)
ax[0].set_ylabel('$error$', fontsize=18)
ax[1].set_ylabel('$error$', fontsize=18)

ax[0].set_title('$k = $'+str(k), fontsize=18)
ax[1].set_title('$k = $'+str(k), fontsize=18)

ax[0].tick_params(direction='in', labelsize=14)
ax[1].tick_params(direction='in', labelsize=14)
fig.tight_layout()
plt.show()
