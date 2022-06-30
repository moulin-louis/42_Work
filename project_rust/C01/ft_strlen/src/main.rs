
fn ft_strlen(phrase:&str) -> i32
{
    phrase.chars().count() as i32
}

fn main() 
{
    let x = ft_strlen("Hello World");
    println!("{}", x);
}
