/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-hoo <svan-hoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:59:02 by svan-hoo          #+#    #+#             */
/*   Updated: 2024/05/28 15:26:42 by svan-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_DEFINES_H
# define FDF_DEFINES_H

# define PI 3.14159265358979

// mlx window
# define WINDOW_TITLE "fdf"
# define WIDTH 1920
# define HEIGHT 1080
# define MENU_WIDTH 400

// fdf defaults
# define DEFAULT_SCALE 0.7
# define ROTATION_SPEED 0.01

// perspective defaults
# define ISO_GAMMA -0.7853981633974483
# define ISO_BETA 0
# define ISO_ALPHA -0.6154729074232804

// general colours
# define C_WHITE			0xFFFFFFFF
# define C_GRAY				0x808080FF
# define C_BLACK			0x000000FF
# define C_BACKGROUND		0x868078FF
# define C_MENU				0xFF000040

// palette RGB
# define P_RGB_NR			0
# define C_RGB_BACK			C_BLACK
# define C_RGB_LOW			0x0000FFFF
# define C_RGB_MID			0x00FF00FF
# define C_RGB_HIGH			0xFF0000FF

// palette HACKERMAN
# define P_HACKERMAN_NR		1
# define C_HACKERMAN_BACK	0x080810FF
# define C_HACKERMAN_LOW	0x003300FF
# define C_HACKERMAN_MID	0x006600FF
# define C_HACKERMAN_HIGH	0x00FF00FF

// palette Metal
# define P_METAL_NR			2
# define C_METAL_BACK		0x202030FF
# define C_METAL_LOW		C_BLACK
# define C_METAL_MID		C_GRAY
# define C_METAL_HIGH		C_WHITE

// palette Rust
# define P_RUST_NR			4
# define C_RUST_BACK		0x080810FF
# define C_RUST_LOW			0x660000FF
# define C_RUST_MID			0xFF6644FF
# define C_RUST_HIGH		0xAAAAAAFF

// palette Earth
# define P_EARTH_NR			5
# define C_EARTH_BACK		C_BLACK
# define C_EARTH_DEEP_SEA	0x202060FF
# define C_EARTH_SEA		0x303090FF
# define C_EARTH_LAND		0x206020FF
# define C_EARTH_MOUNTAIN	0x483038FF
# define C_EARTH_SNOW		0xBBBBBBFF

// palette Pastel
// # define P_PASTEL_NR		6
// # define C_PASTEL_BACK		0x20002088
// # define C_PASTEL_LOW		0x85D65CFF
// # define C_PASTEL_MID		0xFBBBC8FF
// # define C_PASTEL_HIGH		0xFFE840FF

# define S_FULL_SPHERE		0
# define S_HALF_SPHERE		1

#endif