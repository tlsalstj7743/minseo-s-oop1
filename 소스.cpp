#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <cstring>
#include <windows.h>

void clear_canvas(char* canvas, int size)
{
	memset(canvas, ' ', size);
	canvas[size] = '\0';
}

void draw_shape(char* canvas, const char* shape, int pos, int size)
{
	if (!canvas || !shape || size < 0) return;

	int len = strlen(shape);
	if (pos < 0)
	{ // pos = -2, shape_size = 3 "-->"
		if (pos + len <= 0) return;
		shape = shape - pos;
		len = strlen(shape);
		pos = 0;
	}
	if (pos + strlen(shape) >= size)
	{ // pos = 78 shape_size = 3, drawing 78, 79 size - pos
		if (pos >= size) return;
		len = size - pos;
	}
	memcpy(canvas+pos, shape, len);  //canvas+pos�� shape�� �׸� ��ġ
}

void render_canvas(const char* canvas)
{	
	printf("%s\r", canvas);
	Sleep(100);
}



int main()
{
	char canvas[80 + 1];
	//�÷��̾� ����
	float player_hp = 50.0;
	char player_shape[20] = "(^_^)";
	int player_pos = 0;
	bool is_player_vanish = false;
	int count_player_vanish = 0;

	//�� ����
	int count_second_enemy_move = 0; //count_second_enemy_move �� 10�� �Ǹ� 1�� ���
	float enemy_hp = 1.0;
	char enemy_shape[20] = "(+*_*)";
	int enemy_pos = 74;

	//�Ѿ� ����
	const int max_bullets = 70;		//������ �ѹ��� �� �� �ִ� �Ѿ��� 5�������� ������ �Ҵ�� �Ѿ� ���� 10��(11���� ������ ������ 5�߾� ���� ���� ������ int 1��ŭ�� �������� �ϱ⶧��)
	char bullet_shapes[max_bullets][20];
	int bullet_positions[max_bullets];
	int bullet_cooltime = 0;		
	int count_bullet = 0;			//�� ���� ������ ��Ÿ���� ����
	bool bullet_is_fired[max_bullets];
	bool start_bullet_fire = false; //ó�� �ѹ��� ��Ҵ��� ��Ÿ���� bool 
	bool is_ready_magazine = false;	//źâ�� �غ�Ǿ������� ��Ÿ���� bool

	memset(bullet_is_fired, false, sizeof(bool) * max_bullets);


	while (1)
	{

		clear_canvas(canvas, 80);
		/* draw game objects */
		if (player_hp <= 10)
		{
			strcpy(player_shape, "     ");
			count_player_vanish++;
		}
		if (player_hp <= 10 && count_player_vanish == 5)
		{
			strcpy(player_shape, "(x.x)");
			count_player_vanish = 0;
		}
		if (player_hp <= 5 && count_player_vanish == 2)
		{
			strcpy(player_shape, "(x.x)");
			count_player_vanish = 0;
		}
		draw_shape(canvas, player_shape, player_pos, 80);
		if (enemy_hp > 0)
		{
			draw_shape(canvas, enemy_shape, enemy_pos, 80);
		}
		draw_shape(canvas, player_shape, player_pos, 80);
		draw_shape(canvas, enemy_shape, enemy_pos, 80);

		for (int i = 0; i < max_bullets; i++)
		{	
			if (bullet_is_fired[i] == false)
				continue;

			draw_shape(canvas, bullet_shapes[i], bullet_positions[i], 80);
		}

		/* process game logic for each game object */

		if (start_bullet_fire == true)					//źâ�� �غ��ϱ������ ��Ÿ��
		{
			if (bullet_cooltime == 100)					//10�ʰ� ������ źâ�� �غ��
			{
				is_ready_magazine = true;
			}
			else
				bullet_cooltime++;
		}

		for (int i = 0; i < max_bullets; i++)
		{	
				
			
			if (bullet_is_fired[i] == false)
				continue;

			if (bullet_positions[i] + strlen(bullet_shapes[i]) < 0 || bullet_positions[i] >= 80)
			{
				bullet_is_fired[i] = false;
				continue;
			}

			//bullet_is_fird�� true�� ��
			if (player_pos < enemy_pos)
				bullet_positions[i]++;
			else if (player_pos > enemy_pos)
				bullet_positions[i]--;
			else
				bullet_is_fired[i] = false;

			//���� �Ѿ˰��� �浹ó��
			if (enemy_pos == bullet_positions[i] + strlen(bullet_shapes[i]) || enemy_pos + strlen(enemy_shape) == bullet_positions[i])
			{
				strcpy(enemy_shape, "(+x_x)");
				enemy_hp -= 5.0;
				bullet_is_fired[i] = false;
			}


		}

		/* process input event. */

		if (_kbhit())
		{	
			
			char ch = _getch();
			int idx_available_bullet_slot = -1;
			switch (ch)
			{
			case 'a': player_pos--; break;
			case 'd': player_pos++; break;
			case ' ':
				if (count_bullet==5) // ź�� 5�߽�� ���� �� ���߰� 10�� ������ ����(�� źâ�� 5���̱� ����)
					break;
				for (int i = 0; i < max_bullets; i++)
				{
					if (bullet_is_fired[i] == false)
					{
						idx_available_bullet_slot = i;
						break;
					}
				}
				if (idx_available_bullet_slot == -1)
					break;
				// idx_available_bullet_slot is in the range of [0, 9]

				if (player_pos == enemy_pos) // if player collides with enemy, we don't have to fire a bullet.
					break;

				if (player_pos < enemy_pos)
				{
					bullet_positions[idx_available_bullet_slot] = player_pos + strlen(player_shape);
					strcpy(bullet_shapes[idx_available_bullet_slot], "-->");
				}
				else if (enemy_pos < player_pos)
				{
					bullet_positions[idx_available_bullet_slot] = player_pos - strlen("<--");
					strcpy(bullet_shapes[idx_available_bullet_slot], "<--");
				}

				bullet_is_fired[idx_available_bullet_slot] = true;
				start_bullet_fire = true;
				count_bullet++;
				break;
			}
		}
		
		//������ 5���� ��� ���� źâ���� ��ٷ�����
		if (count_bullet == 5 && is_ready_magazine == true)		
		{
			bullet_cooltime = 0;
			start_bullet_fire = false;
			is_ready_magazine = false;
			count_bullet = 0;
			draw_shape(canvas, "ź���� ������ �Ǿ����ϴ�", 40, 80);
		}

		if (count_second_enemy_move == 10)					// 1�ʸ��� �÷��̾ ����
		{
			if (player_pos < enemy_pos)
				enemy_pos--;
			else if (player_pos > enemy_pos)
				enemy_pos++;
			else
				continue;
			count_second_enemy_move = 0;
		}
		
		//�÷��̾�,���� �浹ó��
		if ((player_pos <= enemy_pos && player_pos + strlen(player_shape) >= enemy_pos) ||
			(enemy_pos + strlen(enemy_shape) >= player_pos && enemy_pos + strlen(enemy_shape) <= player_pos + strlen(player_shape))) // �÷��̾�� �� �浹ó��
		{
			strcpy(player_shape, "(X_X)");
			player_hp -= 1.0;
		}
		else
			strcpy(player_shape, "(^_^)");

		//�÷��̾� ������
		
		render_canvas(canvas);
		
		count_second_enemy_move += 1;	//������ �����ϰ� 1�������� ������ �����Ͽ� �ð��� ���
		
		if (player_hp ==0)
			break;
		
	} /* end of while(1) */


	return 0;
}