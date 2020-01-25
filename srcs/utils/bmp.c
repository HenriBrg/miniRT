/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:58:45 by henri             #+#    #+#             */
/*   Updated: 2020/01/25 15:20:48 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

/*
** Code inspiration : https://stackoverflow.com/a/55504419
** http://www.machaon.fr/isn/representation/Les%20fichiers%20images%20BMP.htm
**
** bytesPerPixel = 4
** fileHeaderSize = 14
** infoHeaderSize = 40
** padding = ajustement car chaque ligne doit comporter un nb d’octets * de 4
** BM : signature de fichier
**
** Wiki :
** The bits representing the bitmap pixels are packed in rows.
** The size of each row is rounded up to a multiple of 4 bytes (a 32-bit DWORD)
** by padding. Padding bytes (not necessarily 0) must be appended to the end of
** the rows in order to bring up the length of the rows to a multiple of four
** bytes. When the pixel array is loaded into memory, each row must begin at a
** memory address that is a multiple of 4. This address/offset restriction is
** mandatory only for Pixel Arrays loaded in memory. For file storage purposes,
** only the size of each row must be a multiple of 4 bytes while the file offset
** can be arbitrary. A 24-bit bitmap with Width=1, would have 3 bytes of data
** per row (blue, green, red) and 1 byte of padding, while Width=2 would have 2
** bytes of padding, Width=3 would have 3 bytes of padding, and Width=4 would
** not have any padding at all.
*/

void				writefileheader(int fd, int width, int height)
{
	int				i;
	int				bytes;
	int				padding;
	unsigned char	fileheader[14];

	i = -1;
	while (++i < 14)
		fileheader[i] = (unsigned char)0;
	padding = (4 - (width * 3) % 4) % 4;
	bytes = 14 + 40 + ((3 * width + padding) * height);
	fileheader[0] = (unsigned char)('B');
	fileheader[1] = (unsigned char)('M');
	fileheader[2] = (unsigned char)(bytes);
	fileheader[3] = (unsigned char)(bytes >> 8);
	fileheader[4] = (unsigned char)(bytes >> 16);
	fileheader[5] = (unsigned char)(bytes >> 24);
	fileheader[10] = (unsigned char)(54);
	write(fd, fileheader, 14);
}

void				writebmpheader(int fd, int width, int height)
{
	int				size;
	int				i;
	unsigned char	bmpheader[40];

	i = -1;
	while (++i < 40)
		bmpheader[i] = (unsigned char)0;
	size = width * height * 3;
	bmpheader[0] = (unsigned char)(40);
	bmpheader[4] = (unsigned char)(width);
	bmpheader[5] = (unsigned char)(width >> 8);
	bmpheader[6] = (unsigned char)(width >> 16);
	bmpheader[7] = (unsigned char)(width >> 24);
	bmpheader[8] = (unsigned char)(height);
	bmpheader[9] = (unsigned char)(height >> 8);
	bmpheader[10] = (unsigned char)(height >> 16);
	bmpheader[11] = (unsigned char)(height >> 24);
	bmpheader[12] = (unsigned char)(1);
	bmpheader[14] = (unsigned char)(3 * 8);
	bmpheader[16] = (unsigned char)(0);
	bmpheader[20] = (unsigned char)(size);
	bmpheader[21] = (unsigned char)(size >> 8);
	bmpheader[22] = (unsigned char)(size >> 16);
	bmpheader[23] = (unsigned char)(size >> 24);
	write(fd, bmpheader, 40);
}

void				writepixels(int fd, t_data *data)
{
	int				x;
	int				y;
	char			*pixtab;

	pixtab = data->pixtab;
	y = data->res->height - 1;
	while (y >= 0)
	{
		x = -1;
		while (++x < data->res->width)
			write(fd, &(pixtab[((y * data->res->width + x)) * 4]), 3);
		y--;
	}
}

void				save_to_bmp(t_data *data)
{
	int				fd;

	ft_putendl_fd("ScreenShot en cours ...", 1);
	if ((fd = open("ScreenShot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		clear(data);
		putexit("Erreur d'ouverture BMP");
	}
	writefileheader(fd, data->res->width, data->res->height);
	writebmpheader(fd, data->res->width, data->res->height);
	writepixels(fd, data);
	if (close(fd) == -1)
	{
		clear(data);
		putexit("Erreur de fermeture BMP");
	}
	ft_putendl_fd("... ScreenShot done ", 1);
}
