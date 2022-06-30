fn ft_print_numbers()
{
    let mut nbr = '0';
    while nbr <= '9'
    {
        print!("{}", nbr);
        nbr = (nbr as u8 + 1) as char;
    }
}

fn main() {
    ft_print_numbers();
}
