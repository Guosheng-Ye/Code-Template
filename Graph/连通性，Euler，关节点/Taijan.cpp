template <typename T>
void Graph<T>::Tarjan(int start, int* low, int* dfn, bool* inStack)
{
	low[start] = dfn[start] = ++ind;//赋初值
	s.push(start);//结点压入栈中
	inStack[start] = true;
	for (list<ArcNode>::iterator it = vertexes[start].arc.begin(); it != vertexes[start].arc.end(); it++)
	{
		int j = it->vexIndex;
		if (dfn[j] <= 0)//找奥下一个结点v
		{
			Tarjan(j, low, dfn, inStack);//递归
			low[start] = min(low[start], low[j]);//更新
		}
		else if (inStack[j])	// 顶点j在栈中，说明形成了环，
		{
			//一旦遇到已入栈的点，就将该点作为连通量的根。这里用dfn[j]更新的原因是：这个点可能已经在另一个强连通分量中了但暂时尚未出栈，
			//所以low[start]不一定能到达low[j]但一定能到达dfn[j].
			low[start] = min(low[start], dfn[j]);
		}
	}
	// 如果dfn[start]==low[start]则start可以看作是某一强连通分量子树的根，也说明找到了一个强连通分量，然后对栈进行弹出操作，直到start被弹出。
	if (dfn[start] == low[start])//结点u是强连通分量的根结点
	{
		int u = -1;//将v退栈，为该连通分量额达一个顶点
		while (u != start)
		{
			u = s.top();
			s.pop();
			inStack[u] = false;
			belong[u] = ti;
		}
		ti++;
	}
}
