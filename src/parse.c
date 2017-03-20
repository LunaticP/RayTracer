#include "rtv1.h"

void		ft_error(char *error)
{
	ft_putendl(error);
	exit(0);
}

void		ft_freelst(t_list **list)
{
	t_list	*ptr;
	t_list	*next;
	ptr = *list;
	while(ptr->next)
	{
		free(ptr->content);
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
//	free(ptr->content);
	free(ptr);
}

char		ft_find(char *str, char *find)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(find);
	while(str[i])
	{
		if(str[i] == find[0])
			if(!(ft_strncmp(str, find, len)))
				return(1);
		i++;
	}
	return(0);
}

char		is_in_tab(char **tab, char *find)
{
	int		i;

	i = -1;
	while(tab[++i])
	{
		if(ft_find(tab[i], find))
			return(1);
	}
	return(0);
}

void		is_correct_close(char **file)
{
	int		i;
	int		j;
	int		par;

	i = -1;
	par = 0;
	while(file[++i])
	{
		j = -1;
		while(file[i][++j])
		{
			if(file[i][j] == '{')
				par++;
			if(file[i][j] == '}')
				par--;
		}
	}
	if(par)
		ft_error("[Error] Missing { or } !");
}
/*
char		*get_word_address(char **file, char *word)
{
	int		x;
	int		y;
	int		len;

	len = ft_strlen(word);
	x = -1;
	y = -1;
	
	while(file[++x])
	{
		y = -1;
		while(file[x][++y])
		{
			if(file[x][y] == word[0])
				if(!ft_strncmp(&file[x][y], word))
					return(&file[x][y]);
		}
	}
	return(NULL);
}

t_object	ft_get_objects(char **file)
{
	int		x;
	int		y;
	char	*addr;

	x = -1;
	addr = get_word_address(file, "objects");
	while(file[++x])
	{
		y = -1;
	
	
	
	
	
	}
	
	
	
}
*/


char		*tabtostr(char **tab, char sep)
{
	int		i;
	int		len;
	char	*str;
	char	*ptr;
	int		nbchar;

	i = -1;
	len = 0;
	while(tab[++i])
		len += ft_strlen(tab[i]) + 1;
	str = ft_memalloc(len + 1);
	str[len + 1] = '\0';
	ptr = str;
	i = -1;
	while(tab[++i])
	{
//		ft_putendl(tab[i]);
		nbchar = ft_strlen(tab[i]) + 1;
		ptr = ft_strcpy(ptr, tab[i]);
		ptr[nbchar - 1] = sep;
		ptr += nbchar;
//		ft_putendl(ptr);
	}
//	ft_putstr(str);
	return(str);
}
/*
char		*ft_clear_input(char *file)
{
	char	*out;




}
*/
void		ft_parse(char **file)
{
	char	*scene;
	if(!is_in_tab(file, "objects"))
		ft_putendl("[Warning] Missing objects, your scene will be empty !");
	if(!(is_in_tab(file, "camera")))
		ft_error("[Error]No camera found !");
	if(!(is_in_tab(file, "settings")))
		ft_putendl("[Warning] No settings found, default settings applied !");
	is_correct_close(file);
	scene = tabtostr(file, ':');
	ft_putstr(scene);
}
/*
t_scene		get_scene(char *scene_path)
{
	t_list	*file;
	char	**tab_file;
	t_scene		scene;

	if(!(file = get_file(scene_path)))
		ft_error("Missing scene file !");
	tab_file = ft_lsttotab(file);
	ft_freelst(&file);
	ft_parse(tab_file);
//	ft_puttab(tab_file);
	return(scene);
}
*/

float		ft_get_value(char *str)
{
	float	res;
	int		pos;
	int		neg;

	pos = 0;
	res = ft_atoi(str);
	if(str[0] == '-')
		neg = 1;
	else
		neg = 0;
	while(str[pos] != '.')
		pos++;
	pos++;
	if(neg)
		res -= (float)ft_atoi(&str[pos]) / 1000000;
	else
		res += (float)ft_atoi(&str[pos]) / 1000000;
	return(res);
}

void		*get_addr_point(t_list *dots, int dec)
{
	t_list	*ptr;
	ptr = dots;
	if (!dec)
		return(NULL);
	while(--dec)
		ptr = ptr->next;
return(ptr->content);
}

t_obj		*get_obj(char *path)
{
	t_list		*file;
	char		**data;
	t_obj		*obj;
	t_point		dot;
	t_triangle	tri;
	int			x;
	int			y;

	file = get_file(path);
	data = ft_lsttotab(file);
//	ft_puttab(data);
	ft_putstr("pouet");
	ft_freelst(&file);
	y = 0;
	obj = ft_memalloc(sizeof(t_obj));
//	tmp = malloc(sizeof(t_point));
	while(data[y][0] != 'o')
		y++;
	obj->name = ft_strdup(&data[y][2]);
	ft_putstr(obj->name);
	while(data[y][0] != 'v' && data[y][1] == ' ')
	y++;
//	obj->pts = NULL;
//	obj->pts = malloc(sizeof(t_list));
	while(data[y][0] == 'v' && data[y][1] == ' ')
	{
		x = 2;
//		obj->pts->content = malloc(sizeof(t_point));
//		obj->pts->content_size = sizeof(t_point);
//		obj->pts->content->x = (t_point){.x = ft_get_value(&data[y][x]),
		dot.x = ft_get_value(&data[y][x]);
		while(data[y][x] != ' ')
			x++;
		x++;
//		obj->pts->content->y = ft_get_value(&data[y][x]);
		dot.y = ft_get_value(&data[y][x]);
		while(data[y][x] != ' ')
			x++;
		x++;
		dot.z = ft_get_value(&data[y][x]);
//		obj->pts->content->z = ft_get_value(&data[y][x]);
//		ft_putstr("YOLO");
//		printf("x : %f , y : %f, z : %f \n", dot.x, dot.y, dot.z);
		ft_lstpushback(&obj->pts, &dot, sizeof(dot));
		y++;
//		if(data[y][0] == 'v')
//		{
//			obj->pts->next = malloc(sizeof(t_list));
//			obj->pts = obj->pts->next;
//		}
//		obj->pts->next = NULL;
	}
	ft_lstpushback(&obj->pts, &dot, sizeof(dot));
//	obj->pts = tmp;
	while(data[y][0] != 'f')
		y++;
	while(data[y] && data[y][0] == 'f')
	{
		x = 2;
		tri.p1 = get_addr_point(obj->pts, ft_atoi(&data[y][x]));
		while(data[y][x] != ' ')
			x++;
		x++;
		tri.p2 = get_addr_point(obj->pts, ft_atoi(&data[y][x]));
		while(data[y][x] != ' ')
			x++;
		x++;
		tri.p3 = get_addr_point(obj->pts, ft_atoi(&data[y][x]));
		ft_lstpushback(&obj->tris, &tri, sizeof(tri));
		ft_putnbr(y);
		y++;
	}
//	ft_lstpushback(&obj->tris, &tri, sizeof(tri));
	ft_putendl("LAWL");
	while(obj->pts->next)
	{
		t_point *pt = obj->pts->content;
		printf("x : %f , y : %f, z : %f \n", pt->x, pt->y, pt->z);
		obj->pts = obj->pts->next;
	}
	ft_putendl("------------------------------------------------------------");
	while(obj->tris->next)
	{
		t_triangle *test = obj->tris->content;
		printf("p1 = x : %f , y : %f, z : %f \n", test->p1->x, test->p1->y, test->p1->z);
		printf("p2 = x : %f , y : %f, z : %f \n", test->p2->x, test->p2->y, test->p2->z);
		printf("p3 = x : %f , y : %f, z : %f \n", test->p3->x, test->p3->y, test->p3->z);
		obj->tris = obj->tris->next;
	}
//	ft_puttab(data);
//	while(data[])
	return(obj);
}


