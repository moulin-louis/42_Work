fn ft_print_alphabet()
{
    let mut alph = 'a';
    while alph <= 'z'
    {
        print!("{}", alph);
        alph = (alph as u8 + 1) as char;
    }
}

fn main() {
    ft_print_alphabet();
}
