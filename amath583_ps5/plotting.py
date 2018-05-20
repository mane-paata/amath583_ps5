import matplotlib
matplotlib.use('pdf')
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

import csv
import sys


def plot_vals(x_vals, y_vals_array, legends):
  ''' '''
  for y_vals in y_vals_array:
    plt.plot(x_vals, y_vals)
  
  plt.legend(legends[1:])
  plt.xlabel(legends[0])
  plt.show()


def read_file(infile, read_titles=True):

  x_vals = []
  y_vals_array = []
  legends = []
  with open(infile, 'r') as csvfile:
    reader = csv.reader(csvfile, delimiter='\t')

    for row in reader:
     
      # first row to be titles
      if read_titles:
        legends = row
        for i in range(len(row[1:])):
          y_vals_array.append([])
        read_titles = False
        continue
      
      x_vals.append(int(row[0]))

      for i in range(len(row[1:])):
        y_vals_array[i].append(float(row[i]))
  
  return x_vals, y_vals_array, legends


x, y, l = read_file(sys.argv[1])
plot_vals(x,y,l)




