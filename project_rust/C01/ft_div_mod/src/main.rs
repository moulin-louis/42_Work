fn ft_div_mod(a:i32, b:i32, div:&mut i32, modu:&mut i32)
{
    *div = a / b;
    *modu = a % b; 
}

fn main() {
    let a = 11;
    let b = 5;
    let mut div:i32 = 0;
    let mut modo:i32 = 0;
    ft_div_mod(a, b, &mut div, &mut modo);
    println!("div = {}, mod = {}", div, modo)
}
