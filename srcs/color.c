unsigned int	color_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return r << 24 | g << 16 | b << 8 | 255;
}
