#include "../../includes/minishell.h"

static void	print_token(char *str, t_tokens token) //a supprimer
{
	ft_printf("%s", str);
	if (token == TOK_INFILE)
		ft_printf("<\n");
	else if (token == TOK_TRUNC)
		ft_printf(">\n");
	else if (token == TOK_HEREDOC)
		ft_printf("<<\n");
	else if (token == TOK_APPEND)
		ft_printf(">>\n");
	else if (token == TOK_PIPE)
		ft_printf("|\n");
	else if (token == TOK_AND_OPER)
		ft_printf("&&\n");
	else if (token == TOK_OR_OPER)
		ft_printf("||\n");
	else if (token == TOK_IN_PAR)
		ft_printf("TOK_IN_PAR\n");
	else if (token == TOK_NOT_IN_PAR)
		ft_printf("TOK_NOT_IN_PAR\n");
	else if (token == TOK_NULL)
		ft_printf("(null)\n");
}

static void	print_binary_tree(t_node_ms *binary_tree) //a supprimer
{
	if (binary_tree)
	{
		ft_printf("noeud :\n");
		ft_printf("    first_redir -> %s\n", binary_tree->first_redir);
		ft_printf("        content -> %s\n", binary_tree->content);
		ft_printf("         infile -> %s\n", binary_tree->infile);
		ft_printf("        outfile -> %s\n", binary_tree->outfile);
		print_token("    infile_mode -> ", binary_tree->infile_mode);
		print_token("   outfile_mode -> ", binary_tree->outfile_mode);
		print_token("   operator_pos -> ", binary_tree->operator_pos);
		print_token("       operator -> ", binary_tree->operator);
		ft_printf("\n\n");
	}
}

t_node_ms	*build_binary_tree(t_token_ms *tokens)
{
	t_node_ms	*binary_tree;
	t_tokens	operator_pos;

	operator_pos = detect_operators(tokens);
	if (operator_pos)
	{
		binary_tree = get_list_infos(tokens, operator_pos);
		if (!binary_tree)
			return (NULL);
	}
	else
	{
		binary_tree = get_pipeline_infos(tokens);
		if (!binary_tree)
			return (NULL);
	}
	print_binary_tree(binary_tree);//a supprimer
	return (binary_tree);
}
