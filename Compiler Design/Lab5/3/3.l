
%{
int positive_no = 0, negative_no = 0, pf_no=0, nf_no=0;
%}
digit   [0-9]
number  {digit}+
positive_number \+?{number}
negative_number \-{number}
positive_frac ({positive_number}\.{digit}*)|(\+?\.{number})
negative_frac ({negative_number}\.{digit}*)|(\-\.{number})
%%

{positive_number} positive_no++;
{negative_number} negative_no++;
{positive_frac} pf_no++;
{negative_frac} nf_no++;
%% 
  
  
int main()                                              
{
   
yylex(); 
printf("Positive numbers = %d\n Negative numbers = %d\n Positive float numbers=%d\n Negative float numbers=%d\n",positive_no, negative_no, pf_no, nf_no);
  
return 0; 
}
int yywrap()
{
        return 1;
}
