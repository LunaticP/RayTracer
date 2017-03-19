/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 08:22:24 by aviau             #+#    #+#             */
/*   Updated: 2017/03/08 02:04:41 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

# define _APPLE_
# ifdef _APPLE_
#  define LEFT 123
#  define RIGHT 124
#  define DOWN 125
#  define UP 126
#  define P_UP 116
#  define P_DOWN 121
#  define KP_0 82
#  define KP_1 83
#  define KP_2 84
#  define KP_3 85
#  define KP_4 86
#  define KP_5 87
#  define KP_6 88
#  define KP_7 89
#  define KP_8 91
#  define KP_9 92
#  define KP_P 69
#  define KP_M 78
#  define KP_F 67
#  define KP_D 75
#  define SPACE 49
#  define ESC 53
#  define NUM_1 18
#  define NUM_2 19
#  define NUM_3 20
#  define NUM_4 21
#  define NUM_5 23
#  define NUM_6 22
#  define NUM_7 26
#  define NUM_8 28
#  define NUM_9 25
#  define NUM_0 29
#  define KEY_R 15
#  define KEY_G 5
#  define KEY_B 11
#  define KEY_C 8
// #  define CTRL (256  || 269)
// #  define SHIFT (257  || 258)
# else
#  define LEFT   65361
#  define RIGHT  65363
#  define DOWN   65364
#  define UP     65362
#  define P_UP	 65365
#  define P_DOWN 65366
#  define K_J    106
#  define K_M    109
#  define K_C    99
#  define K_L    108
#  define K_R    114
#  define KP_0   65438
#  define KP_1   65436
#  define KP_2   65433
#  define KP_3   65435
#  define KP_4   65430
#  define KP_5   65437
#  define KP_6   65432
#  define KP_7   65429
#  define KP_8   65431
#  define KP_9   65434
#  define KP_P   65451
#  define KP_M   65453
#  define KP_F   65450
#  define KP_D   65455
#  define SPACE  32
#  define ESC    65307
#  endif
#endif
