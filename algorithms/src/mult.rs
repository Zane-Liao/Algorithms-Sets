//！It currently cannot calculate very large numbers
//! It just simply implements the Karatsuba algorithm.

use num::pow;
use std::cmp::max;


pub fn digits(num: u128) -> usize {
    let mut n = num;
    let mut count:usize = 0;

    while n > 0 {
        count += 1;
        n /= 10;
    }

    return count;
}

pub fn split_at(a: u128, b: usize) -> (u128, u128) {
    let power_of_10 = pow(10, b);
    let low = a % power_of_10;
    let high = a / power_of_10;
    (high, low)
}

// O(n^{2}) ==> O(n^{1.585})
pub fn karatsuba(a: u128, b: u128) -> u128 {
    if a < 10 || b < 10 {
        return a * b;
    }

    let m = max(digits(a), digits(b));
    let m2 = m / 2;

    let (high1, low1) = split_at(a, m2);
    let (high2, low2) = split_at(b, m2);

    let z0 = karatsuba(low1, low2);
    let z1 = karatsuba(low1 + high1, low2 + high2);
    let z2 = karatsuba(high1, high2);

    return (z2 * pow(10, (m2 as u128 *2).try_into().unwrap())) + ((z1 - z2- z0) * pow(10, (m2 as u128).try_into().unwrap())) + z0;
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn test() {
        assert_eq!(karatsuba(2, 19), 38);
        assert_eq!(karatsuba(5000, 5000), 25000000);
        assert_eq!(karatsuba(25, 25), 625);
        assert_eq!(karatsuba(1234, 4567), 5635678);
        assert_eq!(karatsuba(255, 693), 176715);
        assert_eq!(karatsuba(4672347, 462375898), 2160380639892606);
    }
}