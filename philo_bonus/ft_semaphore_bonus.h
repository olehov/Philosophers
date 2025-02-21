/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_semaphore_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:37:44 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/19 16:13:22 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SEMAPHORE_BONUS_H
# define FT_SEMAPHORE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <semaphore.h>

# define SEM_IS_DIED_NAME "/is_died"
# define SEM_IS_FINISHED_NAME "/is_finished"
# define SEM_START_NAME "/start"
# define SEM_CAN_PRINT_NAME "/can_print"
# define SEM_PRINT_NAME "/print"
# define SEM_FORKS_NAME "/forks"
# define SEM_IS_ALL_FULL "/is_all_full"
# define SEM_PHILO_IS_FULL_NAME "/philo_full_id_"
# define SEM_LAST_MEAL_TIME_NAME "/last_meal_time_id_"
# define SEM_IS_FINISH_NAME "/is_finish_"

typedef struct s_sem
{
	sem_t	*is_died;
	sem_t	*is_finished;
	sem_t	*start;
	sem_t	*can_print;
	sem_t	*print;
	sem_t	*is_all_full;
}	t_semapores;

typedef struct s_named_sem
{
	char	*name;
	sem_t	*sem;
}	t_named_sem;

t_semapores	*ft_init_semaphores(void);
t_named_sem	*ft_init_named_semaphore(const char *name, size_t id);

void		ft_destroy_semaphores(t_semapores *sem);
void		ft_destroy_named_semaphore(t_named_sem *sem);
void		close_sem(sem_t *sem, char *name);

#endif