use crate::{Graph, UnGraph};


// Time: O(V^{2}) Space: O(V + E)
pub fn karger_min_cut(un_graph: &Vec<Vec<usize>>) -> usize {
    let mut ug = UnGraph::from_adj(un_graph.to_vec());
    let mut u = &ug.adj[0];
    let mut v = &ug.adj[1];

    0
}

#[cfg(test)]
mod test {
    use super::*;
    use crate::iofile::read_graph;

    #[test]
    fn test() -> Result<(), Box<dyn std::error::Error>> {
        let path = format!("{}/problemFile/KargerMinCut.txt", env!("CARGO_MANIFEST_DIR"));
        let ug = read_graph(&path)?;
        let answer = karger_min_cut(&ug);
        // Random Compute
        println!("{:?}, {:?}", ug.len() - 1, answer);
        // assert_eq!(answer, 17 as usize);
        Ok(())
    }
}