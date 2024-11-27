 #include<stdio.h>
 
 int main()
{
	int i=0;
	int h[9]={0}, x[3]={0}, y[3]={0};
	FILE *input = fopen("../input/4.txt","r");
	
	for(i = 0; i<9; i++) fscanf(input, "%d", &h[i]);
	for(i = 0; i<3; i++) fscanf(input, "%d", &x[i]);
	for(i = 0; i<3; i++) fscanf(input, "%d", &y[i]);
	fclose(input);
	
	int *p_x = &x[0] ;
	int *p_h = &h[0] ;
	int *p_y = &y[0] ;
	
	asm volatile(
		"li t4, 3\n\t"
		"Loop1:\n\t"
		"  addi %[p_x], %[x], 0\n\t"
		"  li t5, 3\n\t"
		"Loop2:\n\t"
		"    lw t0, 0(%[p_h])\n\t"
		"    lw t1, 0(%[p_x])\n\t"
		"    mul t2, t0, t1\n\t"
		"    lw t3, 0(%[p_y])\n\t"
		"    add t3, t3, t2\n\t"
		"    sw t3, 0(%[p_y])\n\t"
		"    addi %[p_x], %[p_x], 4\n\t"
		"    addi %[p_h], %[p_h], 4\n\t"
		"    addi t5, t5, -1\n\t"
		"    bnez t5, Loop2\n\t"
		"  addi %[p_y], %[p_y], 4\n\t"
		"  addi t4, t4, -1\n\t"
		"  bnez t4, Loop1\n\t"
		: [p_h] "+r" (p_h), [p_x] "+r" (p_x), [p_y] "+r" (p_y)
		: [x] "r" (x)
	);
	
	p_y = &y[0];
	for(i = 0; i<3; i++)
		printf("%d \n", *p_y++);
	return(0) ;

}
