use std::fs;
use std::io;

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