use std::fs;
use std::io;
use std::fs::File;
use std::io::BufRead;

#[allow(unused)]
pub fn read_block_file() {
    unimplemented!();
}

pub fn read_file(path_: &str) -> io::Result<Vec<i128>> {
    let contents = fs::read_to_string(path_)?;
    let nums: Vec<i128> = contents
        .lines()
        .filter_map(|line| line.trim().parse::<i128>().ok())
        .collect();

    Ok(nums)
}

pub fn read_graph(path: &str) -> io::Result<Vec<Vec<usize>>> {
    let file = File::open(path)?;
    let mut graph: Vec<Vec<usize>> = vec![];

    for line in io::BufReader::new(file).lines() {
        let line = line?;
        let numbers: Vec<usize> = line
            .split('\t')
            .filter_map(|s| s.parse().ok())
            .collect();
        if numbers.is_empty() { continue; }

        let u = numbers[0];
        while graph.len() <= u {
            graph.push(vec![]);
        }
        for &v in &numbers[1..] {
            while graph.len() <= v {
                graph.push(vec![]);
            }
            graph[u].push(v);
            // Optional
            // graph[v].push(u);
        }
    }
    Ok(graph)
}