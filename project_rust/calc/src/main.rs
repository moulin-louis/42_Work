use std::env;
use std::i64;
use std::i128;

fn add_nbr (nbr_one:i64, nbr_two:i64) {
    let check_overflow:u64 = nbr_one as u64 + nbr_two as u64;
    if check_overflow > i64::MAX as u64{
        println!("Overflow problem");
        return ;
    }
    println!("result = {}", nbr_one + nbr_two);
}

fn remove_nbr(nbr_one:i64, nbr_two:i64) {
    let check_underflow:i128 = nbr_one as i128 - nbr_two as i128;
    if check_underflow < i64
    ::MIN
     as i128 {
        println!("Underflow problem");
        return ;
    }
    println!("result = {}", nbr_one - nbr_two);
}

fn divide_nbr(nbr_one:i64, nbr_two:i64) {
    if nbr_two == 0 {
        println!("cant divie by 0");
        return ;
    }
    println!("result = {}", nbr_one / nbr_two);
}

fn multiply_nbr(nbr_one:i64, nbr_two:i64) {
    if (nbr_one * nbr_two) / nbr_two != nbr_one {
        println!("Overflow problem");
        return ;
    }
    println!("result = {}", nbr_one * nbr_two);
}
fn main() {
    let nbr_one;
    let nbr_two;
    let instruc;

    if env::args().len() != 4 {
        println!("Wrong nbr of args");
        return ;
    }
    
    nbr_one = String::from(env::args().nth(1).expect("cant read args or gib a args"));
    let nbr_one:i64 = nbr_one.trim().parse().expect("Gib a nbr for first args or overflow problem");

    nbr_two = String::from(env::args().nth(3).expect("cant read args or gib a args"));
    let nbr_two:i64 = nbr_two.trim().parse().expect("Gib a nbr for second args or overflow problem");

    instruc = String::from(env::args().nth(2).expect("Cant read args or gib a args"));

    if instruc != "+" && instruc != "-" && instruc != "/" && instruc != "*"{
        println!("Second args istn an instruction");
        return ;
    }
    if instruc == "+" {
        add_nbr(nbr_one, nbr_two);
    }
    else if instruc == "-" {
        remove_nbr(nbr_one, nbr_two);
    }
    else if instruc == "/" {
        divide_nbr(nbr_one, nbr_two);
    }
    else if instruc == "*" {
        multiply_nbr(nbr_one, nbr_two);
    }
}
