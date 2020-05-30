//把编码写进文件
void writecode(int fd_r, int fd_w, struct Filestate *pfilestate, struct huffman *huffman);

void writetocode(char *filename, struct Filestate *pfilestate, struct huffman *huffman);
