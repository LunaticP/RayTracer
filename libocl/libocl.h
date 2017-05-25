/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libocl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jogarcia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 20:31:22 by jogarcia          #+#    #+#             */
/*   Updated: 2017/05/21 20:31:24 by jogarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBOCL_H
# define LIBOCL_H
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif
# include "libft.h"
# include <stdarg.h>

# define CL_SUCCESS 0
# define CL_DEVICE_NOT_FOUND -1
# define CL_DEVICE_NOT_AVAILABLE -2
# define CL_COMPILER_NOT_AVAILABLE -3
# define CL_MEM_OBJECT_ALLOCATION_FAILURE -4
# define CL_OUT_OF_RESOURCES -5
# define CL_OUT_OF_HOST_MEMORY -6
# define CL_PROFILING_INFO_NOT_AVAILABLE -7
# define CL_MEM_COPY_OVERLAP -8
# define CL_IMAGE_FORMAT_MISMATCH -9
# define CL_IMAGE_FORMAT_NOT_SUPPORTED -10
# define CL_BUILD_PROGRAM_FAILURE -11
# define CL_MAP_FAILURE -12
# define CL_MISALIGNED_SUB_BUFFER_OFFSET -13
# define CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST -14
# define CL_COMPILE_PROGRAM_FAILURE -15
# define CL_LINKER_NOT_AVAILABLE -16
# define CL_LINK_PROGRAM_FAILURE -17
# define CL_DEVICE_PARTITION_FAILED -18
# define CL_KERNEL_ARG_INFO_NOT_AVAILABLE -19
# define CL_INVALID_VALUE -30
# define CL_INVALID_DEVICE_TYPE -31
# define CL_INVALID_PLATFORM -32
# define CL_INVALID_DEVICE -33
# define CL_INVALID_CONTEXT -34
# define CL_INVALID_QUEUE_PROPERTIES -35
# define CL_INVALID_COMMAND_QUEUE -36
# define CL_INVALID_HOST_PTR -37
# define CL_INVALID_MEM_OBJECT -38
# define CL_INVALID_IMAGE_FORMAT_DESCRIPTOR -39
# define CL_INVALID_IMAGE_SIZE -40
# define CL_INVALID_SAMPLER -41
# define CL_INVALID_BINARY -42
# define CL_INVALID_BUILD_OPTIONS -43
# define CL_INVALID_PROGRAM -44
# define CL_INVALID_PROGRAM_EXECUTABLE -45
# define CL_INVALID_KERNEL_NAME -46
# define CL_INVALID_KERNEL_DEFINITION -47
# define CL_INVALID_KERNEL -48
# define CL_INVALID_ARG_INDEX -49
# define CL_INVALID_ARG_VALUE -50
# define CL_INVALID_ARG_SIZE -51
# define CL_INVALID_KERNEL_ARGS -52
# define CL_INVALID_WORK_DIMENSION -53
# define CL_INVALID_WORK_GROUP_SIZE -54
# define CL_INVALID_WORK_ITEM_SIZE -55
# define CL_INVALID_GLOBAL_OFFSET -56
# define CL_INVALID_EVENT_WAIT_LIST -57
# define CL_INVALID_EVENT -58
# define CL_INVALID_OPERATION -59
# define CL_INVALID_GL_OBJECT -60
# define CL_INVALID_BUFFER_SIZE -61
# define CL_INVALID_MIP_LEVEL -62
# define CL_INVALID_GLOBAL_WORK_SIZE -63

static const char	*g_error_array[64] = {
	"",
	"CL_DEVICE_NOT_FOUND",
	"CL_DEVICE_NOT_AVAILABLE",
	"CL_COMPILER_NOT_AVAILABLE",
	"CL_MEM_OBJECT_ALLOCATION_FAILURE",
	"CL_OUT_OF_RESOURCES",
	"CL_OUT_OF_HOST_MEMORY",
	"CL_PROFILING_INFO_NOT_AVAILABLE",
	"CL_MEM_COPY_OVERLAP",
	"CL_IMAGE_FORMAT_MISMATCH",
	"CL_IMAGE_FORMAT_NOT_SUPPORTED",
	"CL_BUILD_PROGRAM_FAILURE",
	"CL_MAP_FAILURE",
	"CL_MISALIGNED_SUB_BUFFER_OFFSET",
	"CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST",
	"CL_COMPILE_PROGRAM_FAILURE",
	"CL_LINKER_NOT_AVAILABLE",
	"CL_LINK_PROGRAM_FAILURE",
	"CL_DEVICE_PARTITION_FAILED",
	"CL_KERNEL_ARG_INFO_NOT_AVAILABLE",
	"UNKNOWN_ERROR -20",
	"UNKNOWN_ERROR -21",
	"UNKNOWN_ERROR -22",
	"UNKNOWN_ERROR -23",
	"UNKNOWN_ERROR -24",
	"UNKNOWN_ERROR -25",
	"UNKNOWN_ERROR -26",
	"UNKNOWN_ERROR -27",
	"UNKNOWN_ERROR -28",
	"UNKNOWN_ERROR -29",
	"CL_INVALID_VALUE",
	"CL_INVALID_DEVICE_TYPE",
	"CL_INVALID_PLATFORM",
	"CL_INVALID_DEVICE",
	"CL_INVALID_CONTEXT",
	"CL_INVALID_QUEUE_PROPERTIES",
	"CL_INVALID_COMMAND_QUEUE",
	"CL_INVALID_HOST_PTR",
	"CL_INVALID_MEM_OBJECT",
	"CL_INVALID_IMAGE_FORMAT_DESCRIPTOR",
	"CL_INVALID_IMAGE_SIZE",
	"CL_INVALID_SAMPLER",
	"CL_INVALID_BINARY",
	"CL_INVALID_BUILD_OPTIONS",
	"CL_INVALID_PROGRAM",
	"CL_INVALID_PROGRAM_EXECUTABLE",
	"CL_INVALID_KERNEL_NAME",
	"CL_INVALID_KERNEL_DEFINITION",
	"CL_INVALID_KERNEL",
	"CL_INVALID_ARG_INDEX",
	"CL_INVALID_ARG_VALUE",
	"CL_INVALID_ARG_SIZE",
	"CL_INVALID_KERNEL_ARGS",
	"CL_INVALID_WORK_DIMENSION",
	"CL_INVALID_WORK_GROUP_SIZE",
	"CL_INVALID_WORK_ITEM_SIZE",
	"CL_INVALID_GLOBAL_OFFSET",
	"CL_INVALID_EVENT_WAIT_LIST",
	"CL_INVALID_EVENT",
	"CL_INVALID_OPERATION",
	"CL_INVALID_GL_OBJECT",
	"CL_INVALID_BUFFER_SIZE",
	"CL_INVALID_MIP_LEVEL",
	"CL_INVALID_GLOBAL_WORK_SIZE"
};

typedef struct			s_ocl_kernel
{
	char				*name;
	size_t				work_dim;
	size_t				*public_work_size;
	size_t				nb_obj;
	cl_mem				*memobj;
	size_t				*obj_size;
	void				**write;
	void				**read;
	cl_kernel			kernel;
}						t_ocl_kernel;

typedef struct			s_ocl_prog
{
	cl_device_id		device_id;
	cl_platform_id		platform_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	t_list				*kernel;
}						t_ocl_prog;

t_ocl_prog				ocl_struct_init(void);
t_ocl_kernel			ocl_kernel_init(void);
int						ocl_build_prog(char *filename, size_t max_src_size,
						t_ocl_prog *p);
int						ocl_new_prog(char *filename, size_t max_src_size,
						t_ocl_prog *prog);
/*
** le format du va_arg
** N -> variable nom du kernel (a mettre en premier)
** O -> nouvel argument declarer, recupere sa size_t
** W -> recupere l'addresse d'une variable a copier dans le kernel sur le
** 		dernier argument declarer avant de le lancer
** R -> recupere l'addresse d'une variable sur lequel ecrire les changement
**		appliques par le kernel au lancement a appliquer sur le
** 		dernier argument declarer
*/
int						ocl_new_kernel(t_ocl_prog *prog, size_t nb_obj,
						size_t *pws, const char *format, ...);
int						ocl_get_karg(va_list ap, const char *str,
						t_ocl_kernel *k, t_ocl_prog *p);
t_ocl_kernel			*ocl_get_right_kernel(t_list *start, char *kernel);
int						ocl_enqueue_kernel(t_ocl_prog *prog, char *kernel);
int						ocl_finish(t_ocl_prog p);
int						ocl_error(cl_int ret, const char *from);
int						ocl_free_kernel(t_ocl_prog p);
int						ocl_set_memobj(va_list ap, t_ocl_kernel *k,
						t_ocl_prog *p, int j);
#endif
