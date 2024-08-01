use std::io::{BufWriter, Read, Write};

fn main() {
    use std::io::{stdin, stdout};

    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let input = input.split_ascii_whitespace();
    let mut input = input.map(|s| s.parse::<i32>().unwrap());
    let mut bw = BufWriter::with_capacity(1 << 17, stdout().lock());

    let t = input.next().unwrap();

    for _ in 0..t {
        let a = input.next().unwrap();
        let b = input.next().unwrap();
        writeln!(bw, "{}", a + b).unwrap();
    }
}
