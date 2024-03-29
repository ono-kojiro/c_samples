#!/bin/sh

scripts=$(find ./scripts/ -name "*.sh")

for filepath in $scripts; do
  basename=$(basename $filepath .sh)
  testspec="spec/${basename}_spec.sh"

  cat - << EOS > $testspec
Describe '$filepath'
  
  setup() { :; }

  cleanup() { :; }

  It 'exits status with zero'
    When run source $filepath
    The output should be present
    The status should be success
  End
End
EOS

done

