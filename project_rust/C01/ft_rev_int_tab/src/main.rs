fn ft_rev_int_tab(tab:&mut [i32], size:&mut usize)
{
    let mut ctr:usize = 0;
    let temp = *size;
    let mut x;
    if *size % 2 == 1
    {
        while ctr != *size - 1
        {
            x = tab[ctr];
            tab[ctr] = tab[*size -1];
            tab[*size - 1] = x;
            ctr += 1;
            *size -= 1;
        }
    }
    else if *size %2 == 0
    {
        while ctr != *size
        {
            x = tab[ctr];
            tab[ctr] = tab[*size -1];
            tab[*size - 1] = x;
            ctr += 1;
            *size -= 1;
            if ctr == *size
            {
                return ;
            }
        }
    }
    *size = temp;
}

fn main()
{
    let mut tab: [i32; 3] = [1, 2, 3];
    let mut size = 3;
    println!("{}{}{}", tab[0], tab[1], tab[2]);
    ft_rev_int_tab(&mut tab, &mut size);
    println!("{}{}{}", tab[0], tab[1], tab[2]);

    let mut test2: [i32; 4] = [1, 2, 3, 4];
    size = 4;
    println!("{}{}{}{}", test2[0], test2[1], test2[2], test2[3]);
    ft_rev_int_tab(&mut test2, &mut size);
    println!("{}{}{}{}", test2[0], test2[1], test2[2], test2[3]);
}
