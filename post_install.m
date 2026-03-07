## Copyright (C) 2026 John Donoghue
##  
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License as
## published by the Free Software Foundation; either version 3 of the
## License, or (at your option) any later version.
##      
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
## General Public License for more details.
##      
## You should have received a copy of the GNU General Public License
## along with this program; if not, see
## <http:##www.gnu.org/licenses/>.
          
## post_install
## .mex files expect a .m file of same name in same folder as the mex file
## containing the help of the mex file, but pkg copies .m files from the src
## folder to the base install folder rather than to the arch folder.
##
## This generic post_install s used to copy any .mex file matching .m files
## from the base install to the arch files folder

function post_install (desc)
  try
    if isfield(desc, "archprefix") && ! isempty(desc.archprefix)
      arch = [__octave_config_info__("canonical_host_type"), "-", ...
                      __octave_config_info__("api_version")];

      # get any mex files
      mex = dir (fullfile (desc.archprefix, arch, "*.mex"));

      for idx = 1:length (mex)
        # for any .m file that has name as a mex file, move it to the arch folder
        [~, funcname, ~] = fileparts (mex(idx).name);
        if exist (fullfile (desc.dir, [funcname ".m"]))
          movefile (fullfile (desc.dir, [funcname ".m"]), fullfile (desc.archprefix, arch, [funcname ".m"]));
        endif
      endfor
    endif
  catch
    warning ("error processing post_install %s", lasterr)
  end_try_catch
endfunction
