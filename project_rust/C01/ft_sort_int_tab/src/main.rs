fn check_array(tab:&mut [i32], size:usize) -> bool
{
    let mut x:usize = 1;
    while x < size
    {
        if tab[x - 1] > tab[x]
        {
            return false;
        }
        x += 1;
    }
    true
}

fn ft_sort_int_tab(tab:&mut [i32], size:usize)
{
    let mut x:usize;
    let mut temp:i32;
    while !check_array(tab, size)
    {
        x = 0;
        while x < size - 1
        {
            if tab[x] > tab[x + 1]
            {
                temp = tab[x];
                tab[x] = tab[x + 1];
                tab[x + 1] = temp;
            }
            x += 1;
        }
    }
   
}

fn main() {
    let mut tab: [i32; 4] = [4, 3, 2, 1];
    let size = 4;
    println!("{}{}{}{}", tab[0], tab[1], tab[2], tab[3]);
    ft_sort_int_tab(&mut tab, size);
    println!("{}{}{}{}", tab[0], tab[1], tab[2], tab[3]);
}
