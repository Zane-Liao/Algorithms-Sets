//! Define Graph Structure
//! All graphs are stored as adjacency lists

pub trait Graph {
    fn add_edge(&mut self, u: usize, v: usize);
    fn neigbors(&self, u: usize) -> Vec<usize>;
    fn num_vertices(&self) -> usize;
    fn degree(&self, u: usize) -> usize {
        self.neigbors(u).len()
    }
}

pub struct UnGraph {
    pub adj: Vec<Vec<usize>>,
}

pub struct DiGraph {
    adj: Vec<Vec<usize>>,
}

pub struct WeightGraph<W> {
    adj: Vec<Vec<(usize, W)>>,
}

impl UnGraph {
    pub fn new(n: usize) -> Self {
        Self { adj: vec![Vec::new(); n] }
    }

    pub fn from_adj(adj: Vec<Vec<usize>>) -> Self {
        Self { adj }
    }
}

impl Graph for UnGraph {
    fn add_edge(&mut self, u: usize, v: usize) {
        self.adj[u].push(v);
        self.adj[v].push(u);
    }

    fn neigbors(&self, u: usize) -> Vec<usize> {
        self.adj[u].clone()
    }

    fn num_vertices(&self) -> usize {
        self.adj.len()
    }
}

impl DiGraph {
    pub fn new(n: usize) -> Self {
        Self { adj: vec![Vec::new(); n] }
    }
}

impl Graph for DiGraph {
    fn add_edge(&mut self, u: usize, v: usize) {
        self.adj[u].push(v)
    }

    fn neigbors(&self, u: usize) -> Vec<usize> {
        self.adj[u].clone()
    }

    fn num_vertices(&self) -> usize {
        self.adj.len()
    }
}

impl<W: Copy> WeightGraph<W> {
    pub fn new(n: usize) -> Self {
        Self { adj: vec![Vec::new(); n] }
    }

    pub fn add_edge_weight(&mut self, u: usize, v: usize, w: W) {
        self.adj[u].push((v, w));
        self.adj[v].push((u, w));
    }

    pub fn neigbors_weight(&self, u: usize) -> &Vec<(usize, W)> {
        &self.adj[u]
    }

    pub fn num_vertices_weight(&self) -> usize {
        self.adj.len()
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test_un_graph() {
        let mut ug = UnGraph::new(5);
        ug.add_edge(0, 1);
        ug.add_edge(0, 2);
        ug.add_edge(1, 2);
        println!("{:?}, {:?}", ug.neigbors(0), ug.neigbors(1));
        assert_eq!(ug.adj[0], ug.neigbors(0));
        assert_eq!(ug.adj[1], ug.neigbors(1));
        println!("num_vertices: {:?}, degree: {:?}", ug.num_vertices(), ug.degree(1));
    }

    #[test]
    fn test_di_graph() {
        let mut dg = DiGraph::new(5);
        dg.add_edge(0, 1);
        dg.add_edge(0, 2);
        dg.add_edge(1, 2);
        println!("{:?}, {:?}, {:?}", dg.neigbors(0), dg.neigbors(1), dg.adj[0]);
        assert_eq!(dg.adj[0], dg.neigbors(0));
        assert_eq!(dg.adj[1], dg.neigbors(1));
        println!("num_vertices: {:?}, degree: {:?}", dg.num_vertices(), dg.degree(1));
    }

    #[test]
    fn test_weight_graph() {
        let mut wg = WeightGraph::new(5);
        wg.add_edge_weight(0, 1, 4);
        wg.add_edge_weight(0, 2, 5);
        wg.add_edge_weight(1, 2, 2);
        println!("{:?}, {:?}, {:?}", wg.neigbors_weight(0), wg.neigbors_weight(1), wg.adj[0]);
        assert_eq!(wg.adj[0], *wg.neigbors_weight(0));
        assert_eq!(wg.adj[1], *wg.neigbors_weight(1));
    }
}