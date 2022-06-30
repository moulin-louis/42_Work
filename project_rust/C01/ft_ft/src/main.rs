fn ft_ft(ptr_x :& mut i32 )
{
    *ptr_x = 42;
}

fn main() {
    let mut x:i32 = 41;
    println!("{}", x);
    ft_ft(&mut x);
    print!("{}", x);
}
