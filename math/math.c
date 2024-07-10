/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkotbi <zkotbi@1337.ma>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:51:46 by zkotbi            #+#    #+#             */
/*   Updated: 2024/07/08 17:07:59 by hibenouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double sign(double n)
{
	return ((n >= 0) - (n < 0));
}

double max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double min(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
