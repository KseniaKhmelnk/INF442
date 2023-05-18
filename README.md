# INF442 - SCC & DBSCAN

## Description

Graphs can be partitioned in a multitude of ways. In this project we explore the structure of directed graphs by implementing two clustering algorithm based in some principles:
- DBSCAN (density) 🌐
- Kosaraju (strong connectivity) 🔀

## Usage

- In root folder:

```sh
cmake -B build
cd build
make

{executable_name} < {input_name}
```

## Executables

1. 'dbscan_graph'

    Run dbscan from a graph input (min path length ~ distance)

2. 'dbscan_point'
    
    Run dbscan from a 2D-points input (euclidean distance)

3. 'kosaraju'

    Run kosaraju from a graph input 

## Inputs 

- 'dbscan_graph' and 'kosaraju' expect graph inputs in the following format:

```txt
<nubmer of vertices> <number of edges>

<from> <to>                             # edge list
<from> <to>
...          
```

- 'dbscan_point' expects 2D-points input in the following format:

```txt
<number of points>

<x coordinate> <y coordinate>           # list of points      
<x coordinate> <y coordinate>
...
```

## Repo structure

- directories

```markdown
.
├── csv                                 # data used in analysis
├── dataset                             # input graphs examples
├── dbscan                              # dbscan implementation
├── gen-data                            # generate data files
├── kosaraju                            # kosaraju implementation
```

- driver programs

```markdown
├── main-dbscan-dmatrix.cpp             # run dbscan from a directed graph input
├── main-dbscan-point.cpp               # run dbscan from 2D-points input
└── main-kosaraju.cpp                   # run kosaraju fom a directed graph input
```

