/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:42 by alucas-           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void error_callback(int error, const char* description)
{
	ft_dprintf(STDERR_FILENO, "Error: %s %d\n", description, error);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action)
{
	(void)scancode;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
	GLFWwindow* window;
	if (!glfwInit())
		return (EXIT_FAILURE);
	glfwSetErrorCallback(error_callback);
	window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, (GLFWkeyfun)key_callback);
	if (!window)
	{
		glfwTerminate();
		return (EXIT_FAILURE);
	}
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return (EXIT_SUCCESS);
}
