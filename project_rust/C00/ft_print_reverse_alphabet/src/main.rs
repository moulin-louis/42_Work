fn ft_print_reverse_alphabet()
{
    let mut alph = 'z';
    while alph >= 'a'
    {
        print!("{}", alph);
        alph =(alph as u8 - 1) as char;
    }
}

fn main() {
    ft_print_reverse_alphabet();
}
