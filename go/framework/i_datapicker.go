package framework

type IDataPicker interface {
	IsPathValid(path string) bool
	PickImport(line string) (ret string, ok bool)
	PickInherit(line string) (ret string ,ok bool)
	PickAbsoluteClass(line string) (ret string, ok bool)
}
