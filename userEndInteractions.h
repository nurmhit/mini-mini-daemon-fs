//
// Created by Мхитарян Нарек on 17/05/2020.
//

#pragma once

void rmrf(char* filename);

void cat(char* filename);

void ret_text(char* filename, char* place);

void mkdir(char *name);

void ls();

void cd(char* dirname);

void create_file_system();

void ls_test();

void greetings();

void interactions_with_user();

void cur_path();

int get_next_dir_name(int start, char* long_path, char* place);

void cp(char* filename, char* destination);

void move(char* filename, char* destination);

void load(char *filename);

void store(char *filename);