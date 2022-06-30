fn ft_ultimate_div_mod(a:&mut i32, b:&mut i32)
{
    let div = *a / *b;
    let modu = *a % *b;
    *a = div;
    *b = modu;
}

fn main() {
    let mut a:i32 = 11;
    let mut b:i32 = 5;
    ft_ultimate_div_mod(&mut a, &mut b);
    println!("div = {}, modulo = {}", a, b);
}
