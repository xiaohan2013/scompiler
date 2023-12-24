; ModuleID = 'Add.c'
source_filename = "Add.c"

define i32 @Add(i32 %a, i32 %b) {
entry:
  %result = add i32 %a, %b
  ret i32 %result
}
