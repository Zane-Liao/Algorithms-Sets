use crate::iofile::read_file;


pub fn min_cut(nums: Vec<i128>) -> i128 {
    
    0
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test() -> Result<(), Box<dyn std::error::Error>> {
        let path = format!("{}/problemFile/KargerMinCut.txt", env!("CARGO_MANIFEST_DIR"));
        let numbers = read_file(&path)?;
        let answer = min_cut(numbers);
        assert_eq!(answer, 17 as i128);
        Ok(())
    }
}