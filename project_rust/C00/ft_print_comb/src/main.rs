fn ft_putchar(c: char)
{
    print!("{}", c);
}

fn ft_print(i :char, j :char, k :char)
{
    if i == '7' && j == '8' && k == '9'
    {
        print!("789");
        return ;
    }
    ft_putchar(i);
    ft_putchar(j);
    ft_putchar(k);
    ft_putchar(',');
    ft_putchar(' ');

}


fn main() {
    let mut i = '0';
    let mut j = '1';
    let mut k = '2';

    while i <= '7'
    {
        while j <= '8'
        {
            while k <= '9'
            {
                ft_print(i, j, k);
                k = (k as u8 + 1) as char;
            }
            j = (j as u8 + 1) as char;
            k = j;
        }
        i = (i as u8 + 1) as char;
        j = i;
    }
}
