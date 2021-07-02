# coding: utf-8
import math
import itertools

semester_std = 6
months_per_semester=6    
fix1=812+20+10
fix2=812+40+10
kapital=21622+20032

module_total= 36

semester_red_s = [4,5,6]  # iterrate 6, 5, 4

def calc_total_semesters(semester_red):
    n_red_mod=(module_total-semester_std)/semester_red
    return math.ceil(1+n_red_mod)

# iterate
k_var=range(250,500,50)  # 0 aint realistic, 100 too
# todo kfw
# todo erhöhte studiengebühren ab semester 6
monthly_income=[0,*range(450,1300,100)]

variations = itertools.product(
    semester_red_s,
    k_var,
    monthly_income,
    range(200,2100,100),  # auslandssemester
    range(100,700, 50),  # studienkredit
    )

def calc_with_variable_cost(k_var):
    kosten1=fix1+k_var
    kosten2=fix2+k_var
    return months_per_semester*(kosten1)+months_per_semester*semester_total*(kosten2)
seen = set()
for reduced_semester, var_cost, income, auslandssemester, studienkredit in variations:
    semester_total=calc_total_semesters(reduced_semester)
    monate_total=semester_total*months_per_semester
    if (reduced_semester, var_cost, income, auslandssemester, monate_total) in seen:
        continue  # bail eraly, we only need threshold. might not be optimum tho
    kosten_monat=calc_with_variable_cost(var_cost)/monate_total
    total_income=income*(monate_total-semester_std-6)  # current semester is out, also ausland
    credits=(studienkredit*monate_total)
    new_capital=(
            kapital
            +total_income
            -(auslandssemester*6)
            +credits
        )
    runway=math.floor(new_capital/kosten_monat)
    restkapital=new_capital-calc_with_variable_cost(var_cost)
    runway_left=runway>=monate_total
    equilibirum = runway==monate_total
    if runway_left and restkapital >= kosten_monat*3:
    # if equilibirum:
        seen.add((reduced_semester, var_cost, income, auslandssemester, monate_total))
        print(f"reduced: {reduced_semester} "
                f"var: {var_cost} income: {income} ausland: {auslandssemester} "
                f"months: {monate_total} semester: {monate_total/months_per_semester}"
                f" runway: {runway} rest: {restkapital} schulden: {studienkredit*monate_total}")
