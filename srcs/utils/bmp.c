/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:58:45 by henri             #+#    #+#             */
/*   Updated: 2019/12/23 02:29:53 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

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

unsigned char *fileheader(int width, int height)
{
	int				bytes;
	int				padding;
	static unsigned char	fileheader[] = {0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0, 0};

	padding = (4 - (width * 3) % 4) % 4;
	bytes = 14 + 40 + (width * 3 + padding) * height;
	fileheader[0] = (unsigned char)('B');
	fileheader[1] = (unsigned char)('M');
	fileheader[2] = (unsigned char)(bytes);
	fileheader[3] = (unsigned char)(bytes >> 8);
	fileheader[4] = (unsigned char)(bytes >> 16);
	fileheader[5] = (unsigned char)(bytes >> 24);
	fileheader[10] = (unsigned char)(54);
	return (fileheader);
}

/*
** unsigned char bmpheader[] = {
** 		0,0,0,0 --> header size
** 		0,0,0,0 --> image width
** 		0,0,0,0 --> image height
** 		0,0 	--> number of color planes
** 		0,0 	--> bits per pixel
** 		0,0,0,0 --> compression
** 		0,0,0,0 --> image size
** 		0,0,0,0 --> horizontal resolution
** 		0,0,0,0 --> vertical resolution
** 		0,0,0,0 --> colors in color table
** 		0,0,0,0 --> important color count
** };
*/


unsigned char *bmpheader(int width, int height)
{
    static unsigned char bmpheader[] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };

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
	return (bmpheader);
}


void 	writepixels(int fd, t_data *data)
{
	int	x;
	int	y;

	y = data->res->height - 1;
	while (y >= 0)
	{
		x = -1;
		while (++x < data->res->width)
			write(fd, &(data->pixtab[(y * data->res->width + x) * 4]), 3);
		y--;
	}
}

void 	save_to_bmp(t_data *data)
{
	int				fd;
	unsigned char	*fheader;
	unsigned char	*bitmapheader;

	ft_putendl_fd("ScreenShot en cours ...", 1);
	fheader = fileheader(data->res->width, data->res->height - 1);
	bitmapheader = bmpheader(data->res->width, data->res->height - 1);
	fd = open("ScreenShot.bmp", O_CREAT | O_WRONLY | O_TRUNC);
	write(fd, fheader, 14);
	write(fd, bitmapheader, 40);
	writepixels(fd, data);
	close(fd);
	ft_putendl_fd("... ScreenShot done !", 1);
}
