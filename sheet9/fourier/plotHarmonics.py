# @author: Arijit Dutta
# @created: 11.01.2022
# @modified: 11.01.2022

import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
rc("text", usetex=True)

Nint=1000
mid = int(Nint/2)
N = [2, 4, 6, 8, 100]
filesim='fourier_simpson_N'
filetrap='fourier_trapezoid_N'

plt.rcParams["axes.prop_cycle"] = plt.cycler("color", plt.cm.Accent.colors)
fig, ax = plt.subplots(1, figsize=(4,4))
plt.rcParams["axes.prop_cycle"] = plt.cycler("color", plt.cm.tab10.colors)
fig1, bx = plt.subplots(1, 5, sharey=True, figsize=(20,4))
plt.rcParams["axes.prop_cycle"] = plt.cycler("color", plt.cm.tab10.colors)
fig2, cx = plt.subplots(figsize=(4,4))

eps = np.array([]).reshape(0,3)
for idx, val in enumerate(N):
    d = np.loadtxt(filetrap+str(val)+'_Nint'+str(Nint)+'.dat')
    bx[idx].plot(d[:,0], d[:,3], lw=0.8, label='trap')
    tr = np.abs(d[mid,3]-d[mid,1])
    #bx[1].plot(d[:,0], d[:,3], lw=0.8)
    d = np.loadtxt(filesim+str(val)+'_Nint'+str(Nint)+'.dat')
    ax.plot(d[:,0], d[:,3], lw=0.8, label=str(val), alpha=1)
    bx[idx].plot(d[:,0], d[:,3], lw=0.8, label='sims')
    bx[idx].plot(d[:,0], d[:,2], lw=0.8, label='analytic')
    bx[idx].plot(d[:,0], d[:,1], lw=0.8, label='exact')
    sm = np.abs(d[mid,3]-d[mid,1])
    th = np.abs(d[mid,2]-d[mid,1])
    eps = np.vstack([eps, [tr, sm, th]])

    bx[idx].tick_params(direction='in', labelsize=16)
    bx[idx].set_xlabel('$x$', fontsize=16)
    bx[idx].set_title('$N = $'+str(val), fontsize=16)

ax.tick_params(direction='in', labelsize=16)
ax.set_xlabel('$x$', fontsize=16)
ax.set_ylabel('$s(x)$', fontsize=16)
ax.set_title('$Nint = $'+str(Nint), fontsize=16)
leg = ax.legend(fontsize=16, frameon=False)

bx[0].set_ylabel('$s(x)$', fontsize=16)
leg1 = bx[0].legend(fontsize=16, frameon=False)

print(eps)
cx.plot(N, eps[:,0], marker='o', markerfacecolor='none', lw=0.8, label='trap')
cx.plot(N, eps[:,1], marker='s', markerfacecolor='none', lw=0.8, label='sims')
cx.plot(N, eps[:,2], marker='d', markerfacecolor='none', lw=0.8, label='exact')
cx.tick_params(direction='in', labelsize=16)
cx.set_xlabel('$N$', fontsize=16)
cx.set_ylabel('$|S_{N}(T/2N)-f(T/2N)|$', fontsize=16)
cx.set_title('$Nint = $'+str(Nint), fontsize=16)
leg2 = cx.legend(fontsize=16, frameon=False)
fig.tight_layout()
fig1.tight_layout()
fig2.tight_layout()
plt.show()
