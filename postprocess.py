
# coding: utf-8

# In[414]:

import numpy as np
from scipy.signal import correlate
import matplotlib.pyplot as plt


# In[415]:

data = np.loadtxt("output.csv")


# In[416]:

plt.plot(data[:,0], data[:,1], label="S")
plt.plot(data[:,0], data[:,2], label="I")
plt.plot(data[:,0], data[:,3], label="R")
plt.title("Número de indivíduos x Tempo")
plt.ylabel("Número de indivíduos")
plt.xlabel("Iteração")
plt.legend()
plt.show()


# In[417]:

cSI = correlate(data[:, 1], data[:, 2], 'same')
cSI = cSI / max(cSI)
cSR = correlate(data[:, 1], data[:, 3], 'same')
cSR = cSR / max(cSR)
cRI = correlate(data[:, 2], data[:, 3], 'same')
cRI = cRI / max(cRI)
cSS = correlate(data[:, 1], data[:, 1], 'same')
cSS = cSS / max(cSS)
cII = correlate(data[:, 2], data[:, 2], 'same')
cII = cII / max(cII)
cRR = correlate(data[:, 3], data[:, 3], 'same')
cRR = cRR / max(cRR)


# In[418]:

plt.subplot(1,2,1)
plt.plot(cSI, label='SI')
plt.plot(cSR, label='SR')
plt.plot(cRI, label='RI')
plt.legend()
plt.subplot(1,2,2)
plt.plot(cSS, label='SS')
plt.plot(cII, label='II')
plt.plot(cRR, label='RR')
plt.legend()
plt.show()


# In[ ]:




# In[ ]:




# In[ ]:



