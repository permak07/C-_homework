import matplotlib.pyplot as plt
import numpy as np

n = np.array([1000, 5000, 10000, 50000, 100000, 500000, 1000000])
time = np.array([0.000513, 0.014293, 0.056239, 1.187, 4.62685, 113.225, 463.331])

k = np.linspace(0, 1000000, 100)

o_n = (time[-1] / n[-1]) * k
o_n2 = (time[-1] / (n[-1]**2)) * (k**2)

plt.figure(figsize=(10, 6))
plt.plot(n, time, 'o-', label='Измеренные данные', color='tab:blue', linewidth=2)
plt.plot(k, o_n, '--', label='O(N)', color='tab:orange')
plt.plot(k, o_n2, ':', label='O(N²)', color='tab:green')

plt.title('Зависимость времени от N')
plt.xlabel('N')
plt.ylabel('Время (сек)')
plt.grid(True)
plt.legend()
plt.show()