#include "ResourceManager.h"
#include "DxLib.h"

const std::vector<int>& ResourceManager::GetImageResource(const std::string& file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	// �R���e�i���ɉ摜�f�[�^�������ꍇ�A�摜�ǂݍ��݂��s��
	if (image_container.count(file_name) == NULL)
	{
		// �����ǂݍ��݂��s���H�s��Ȃ��H
		if (all_num != 1)
		{
			// �����ǂݍ��݂��s��
			CreateImagesResource(file_name, all_num, num_x, num_y, size_x, size_y);
		}
		if (all_num == 1)
		{
			// �����ǂݍ��݂��s��Ȃ�
			CreateImageResource(file_name);
		}

	}

	// �R���e�i���̃f�[�^��Ԃ�
	return image_container[file_name];
}

const int& ResourceManager::GetSoundResource(const std::string& file_path)
{
	// �R���e�i���Ɏw��t�@�C����������΁A��������
	if (sound_container.count(file_path) == NULL)
	{
		// �����̓ǂݍ��݂��s��
		CreateSoundsResource(file_path);
	}

	// �R���e�i���̃f�[�^��Ԃ�
	return sound_container[file_path];
}

void ResourceManager::UnloadAllResourceData()
{
	UnloadImageResourceData();
	UnloadSoundResourceData();
}

void ResourceManager::CreateImageResource(const std::string& file_path)
{
	// �w�肳�ꂽ�摜�t�@�C���ǂݍ���
	int handle = LoadGraph(file_path.c_str());

	// �G���[�`�F�b�N
	if (handle == -1)
	{
		throw (file_path + "������܂���\n");
	}

	// �R���e�i�ɓǂݍ��񂾉摜��ǉ�����
	image_container[file_path].push_back(handle);
}

void ResourceManager::CreateImagesResource(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	// ��������摜���������������m�ۂ���
	int* handle = new int[all_num];

	// �w�肳�ꂽ�摜�t�@�C���𕪊��œǂݍ���
	int result = LoadDivGraph(file_name.c_str(), all_num, num_x, num_y, size_x, size_y, handle);

	// �G���[�`�F�b�N
	if (result == -1)
	{
		throw (file_name + "������܂���\n");
	}

	// �R���e�i�ɓǂݍ��񂾉摜��ǉ�����
	for (int i = 0; i < all_num; i++)
	{
		image_container[file_name].push_back(handle[i]);
	}

	// �m�ۂ������������������
	delete[] handle;
}

void ResourceManager::CreateSoundsResource(std::string file_path)
{
	// �w�肳�ꂽ�t�@�C����ǂݍ���
	int handle = LoadSoundMem(file_path.c_str());

	// �G���[�`�F�b�N
	if (handle == -1)
	{
		throw (file_path + "������܂���\n");
	}

	// �R���e�i�ɓǂݍ��񂾉�����ǉ�����
	sound_container[file_path] = handle;
}

void ResourceManager::UnloadImageResourceData()
{
	// �R���e�i���ɉ摜��������΁A�������I������
	if (image_container.size() == NULL)
	{
		return;
	}

	// �S�Ẳ摜���폜
	for (std::pair<std::string, std::vector<int>> value : image_container)
	{
		DeleteSharingGraph(value.second[0]);
		value.second.clear();
	}

	// �R���e�i�����
	image_container.clear();
}

void ResourceManager::UnloadSoundResourceData()
{
	// �R���e�i���ɉ�����������΁A�������I������
	if (sound_container.size() == NULL)
	{
		return;
	}

	// �S�Ẳ������폜
	for (std::pair<std::string, int> value : sound_container)
	{
		DeleteSoundMem(value.second);
	}

	// �R���e�i�����
	sound_container.clear();
}