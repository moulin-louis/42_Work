fn  ft_putnbr(x :i64)
{
    let mut nbr = x;
    if nbr < 0
    {
        print!("-");
        nbr = nbr * -1;
    }
    if nbr >= 10
    {
        ft_putnbr(nbr / 10);
        ft_putnbr(nbr % 10);
    }
    if nbr >= 0 && nbr <= 9
    {
        print!("{}", nbr);
    }
}

fn main() {
    ft_putnbr(2147483648);
}
