import matplotlib.pyplot as plt
import sys
import getopt

def main(*args, **kwargs):
    
    # Get command line options
    args = sys.argv
    optlist, _ = getopt.getopt(args[1:], 'o:')
    operation = optlist[0][1]

    file = open(f'stats.out', 'r+')

    dims = []
    blas_stats = []
    blis_stats = []

    # Parse the file
    for line in file:
        l = line.split(', ')
        dims.append(l[0])
        blas_stats.append(float(l[1]))
        blis_stats.append(float(l[2]))
    
    # Build graph
    plt.plot(dims, blas_stats, label="BLAS")
    plt.plot(dims, blis_stats, label='BLIS')
    plt.xticks([f'{i}' for i in range(4, 64, 4)])
    plt.xlabel("n")
    plt.ylabel("Gflops/s")
    plt.title(f"{operation} Performance On Small Matrices")
    plt.legend()
    plt.savefig(f'figs/{operation}.png')



if __name__=='__main__':
    main()