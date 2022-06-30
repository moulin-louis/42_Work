fn ft_swap(ptr_a:& mut u32, ptr_b:& mut u32)
{
    let temp = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = temp;
}

fn main() {
    let mut x = 1;
    let mut y = 5;
    ft_swap(& mut x, & mut y);
    println!("x = {}, y = {}", x, y);
}
