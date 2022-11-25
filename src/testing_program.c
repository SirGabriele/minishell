#include "../includes/minishell.h"

void	print_binary_tree_token(char *str, t_tokens token)
{
	ft_printf("%s", str);
	if (token == TOK_INFILE)
		ft_printf("INFILE\n");
	else if (token == TOK_TRUNC)
		ft_printf("TRUNC\n");
	else if (token == TOK_HEREDOC)
		ft_printf("HEREDOC\n");
	else if (token == TOK_APPEND)
		ft_printf("APPEND\n");
}

void	print_binary_tree(t_node_ms *binary_tree, i)
{
	if (binary_tree)
	{
		ft_printf("noeud %d :\n", i);
		ft_printf("    first_redir -> %s", binary_tree->first_redir);
		ft_printf("        content -> %s", binary_tree->content);
		ft_printf("         infile -> %s", binary_tree->infile);
		ft_printf("        outfile -> %s", binary_tree->outfile);
		print_binary_tree_token("    infile_mode -> ", binary_tree->infile_mode);
		print_binary_tree_token("   outfile_mode -> ", binary_tree->outfile_mode);
		print_binary_tree_token("   operator_pos -> ", binary_tree->operator_pos);
		print_binary_tree_token("       operator -> ", binary_tree->operator);
		ft_printf("\n\n");
	}
	print_binary_tree(binary_tree->left, i +1);
	print_binary_tree(binary_tree->right, i +1);
}
