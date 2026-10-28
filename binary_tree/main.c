#include"binary_tree.h"
#include<stdio.h>
#include<stdlib.h>
// 辅助函数：将树以层序方式写入 JSON 文件，格式如 [9,4,12,3,5,null,null,2,1]
void write_tree_to_json(node* root, const char* filename) {
	FILE* f = fopen(filename, "w");
	if (!f) return;

	fprintf(f, "[");
	if (root != NULL) {
		// 简易队列
		int cap = 1024;
		node** queue = (node**)malloc(sizeof(node*) * cap);
		int head = 0, tail = 0;
		queue[tail++] = root;
		int first = 1;

		while (head < tail) {
			node* cur = queue[head++];
			if (!first) fprintf(f, ",");
			first = 0;

			if (cur == NULL) {
				fprintf(f, "null");
			}
			else {
				fprintf(f, "%d", cur->num);   // ✅ 这里才是正确写法
				queue[tail++] = cur->left_child;
				queue[tail++] = cur->right_child;
			}
		}
		free(queue);
	}
	fprintf(f, "]");
	fclose(f);
}
int main(void) {
	//int nums[20] = { 2,5,7 };
	/*
	int len = sizeof(nums) / sizeof(nums[0]);
	printf("%d", len);
	*/

	node* root = insert(9, NULL);
	int arr[12] = { 2,3,10,-8,-10,32,22,89,16,-1,0,15 };
	for (int i = 0; i < 12; i++) {
		root = insert(arr[i], root);
	}
	//node* max_node = find_max(root);
	//printf("%d\n", max_node->num);

	//root=recursion_delete_node(12, root);
	//printf_tree(root);
	const char* temp_file = "tree_data.json";
	write_tree_to_json(root, temp_file);

	// 3. 构造并执行Python命令
	// 注意：路径中的反斜杠在C字符串中需要转义（\\）
	// 如果路径包含空格，建议用双引号将整个路径括起来
	const char* python_script = "D:\\PycharmProjects\\pycharmmiscproject_1\\data-structure\\print-BST.py";

	char command[512];
	// 格式：python "脚本路径" "数据文件路径"
	snprintf(command, sizeof(command), "python \"%s\" \"%s\"", python_script, temp_file);

	printf("Executing: %s\n", command);
	int result = system(command);

	if (result == 0) {
		printf("Python script executed successfully.\n");
	}
	else {
		printf("Python script failed with code: %d\n", result);
	}
	return 0;
};
/*
t0  C: main() 开始
t1  C: insert(9, NULL)          → 建根节点
t2  C: for 12 次 insert(...)    → 构建完整 BST（内存里）
t3  C: write_tree_to_json(...)
	   ├─ fopen("tree_data.json","w")
	   ├─ 层序遍历，fprintf 逐个写
	   └─ fclose                        ← 此刻文件落盘
t4  C: snprintf 拼出命令字符串
t5  C: system(command)  ────────────┐
	   (C 阻塞等待)                  │
	   ┌─────────────────────────────┘
	   │ t6  Python: 解释器启动，__name__=='__main__'
	   │ t7  Python: sys.argv 检查，取 argv[1]
	   │ t8  Python: open + json.load   ← 读 t3 写的文件
	   │ t9  Python: build_tree(values) → 重建 Python 树
	   │ t10 Python: print_tree_indent → 打印到 stdout
	   │ t11 Python: 脚本正常结束，退出码 0
	   └─────────────────────────────┐
t12 C: system 返回 0 ◄───────────────┘
t13 C: 打印 "successfully"
t14 C: return 0 → 进程 A 退出
*/